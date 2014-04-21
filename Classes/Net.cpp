#include "Net.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <winsock2.h>
#else
#include <unistd.h>
#endif


int Net::onMsgLuaCallback = 0;

Net::Net(): client(0)
{
	msgQueue.clear();
}

Net::~Net()
{
	if(client)
	{
		pc_client_destroy(client); 
	}
	msgQueue.clear();
}

void Net::nonSyncConnect()
{
	struct sockaddr_in address;
	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip.c_str());

	if(pc_client_connect(client, &address))
	{
		pushMsg(PC_EVENT_CONNECTEFAIL, "");
		int a = 3;
	}
	else
	{
		pushMsg(PC_EVENT_CONNECTED, "");
	}
}
void Net::connect(const char *ip_, int port_)
{
	pc_client_t *pre_client = client;
	client = pc_client_new();
	if(pre_client)
	{
		//pc_client_destroy(pre_client);
	}

	ip = ip_;
	port = port_;

	auto t = std::thread(&Net::nonSyncConnect, this);
    t.detach();
}

void Net::addListener(const char* event)
{
	pc_add_listener(client, event, &Net::pomeloMsgCallBack);
}

void Net::removeListener(const char* event)
{
	pc_remove_listener(client, event, &Net::pomeloMsgCallBack);
}

void Net::pomeloNotify(const char *route, const char *str)
{
	pc_notify_t *notify = pc_notify_new();
	json_error_t error;
	json_t *msg = json_loads(str, JSON_DECODE_ANY, &error);
	if(!msg)
	{
		pushMsg(std::string(route), std::string("{\"error\":true}"));
		pushMsg(std::string(PC_EVENT_REQUESTERR), std::string(""));
	}
	else
	{
		pc_notify(client, notify, route, msg, &Net::pomeloNotifyCallBack);
		//json_decref(msg);
	}
}

void Net::pomeloRequest(const char *route, const char *str)
{
	pc_request_t *request = pc_request_new();
	json_error_t error;
	json_t *msg = json_loads(str, JSON_DECODE_ANY, &error);
	if(!msg)
	{
		pushMsg(std::string(route), std::string("{\"error\":true}"));
		pushMsg(std::string(PC_EVENT_REQUESTERR), std::string(""));
	}
	else
	{
		pc_request(client, request, route, msg, &Net::pomeloRequestCallBack);
		//json_decref(msg);
	}
}

bool Net::httpRequest(std::string & url, int cbFunc)
{
	HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(Net::httpResponse));

	char buf[16] = {0};
	sprintf(buf, "%x", cbFunc);
	std::string tag(buf);
    request->setTag(tag.c_str());

	requestMap[tag] = cbFunc;

    HttpClient::getInstance()->send(request);
    request->release();
	return true;
}

void Net::httpResponse(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
	bool ret = false;

	std::string tag(response->getHttpRequest()->getTag());
	if(!requestMap[tag])
	{
		return;
	}
    
    //int statusCode = response->getResponseCode();
    //char statusString[64] = {0};
    //sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //log("response code: %d", statusCode);
    
	std::string value;
    if (!response->isSucceed()) 
    {
        ret = false;
        value = std::string(response->getErrorBuffer());
    }
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		char *data = new char[buffer->size()+1];
		for (unsigned int i = 0; i < buffer->size(); i++)
		{
			data[i] = (*buffer)[i];
		}
		data[buffer->size()] = 0;
		value = std::string(data);
		delete [] data;
	}

	auto L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_pushboolean(L, ret);
  	lua_pushstring(L, value.c_str());
  	LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(requestMap[tag], 2);
	requestMap[tag] = 0;
}

void Net::registerOnMsgLuaCallBack(int luaCallback)
{
	onMsgLuaCallback = luaCallback;
}

void Net::visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated)
{
	if(!msgQueue.empty())
	{
		handleMsg();
	}
}

void Net::handleMsg()
{
	if(onMsgLuaCallback)
	{
		auto L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
		auto msg = msgQueue.front();
		lua_pushstring(L, msg["event"].c_str());
		lua_pushstring(L, msg["msg"].c_str());
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(onMsgLuaCallback, 2);
		msgQueue.pop_front();
	}
}

void Net::pushMsg(std::string event, std::string msg)
{
	std::map<std::string, std::string> m;
	m["event"] = event;
	m["msg"] = msg;
	msgQueue.push_back(m);
}

void Net::pomeloNotifyCallBack(pc_notify_t *req, int status)
{
	auto event = req->route;
	if(status == -1)
	{
		Net::getInstance()->pushMsg(std::string(event), std::string("{\"error\":true}"));
		Net::getInstance()->pushMsg(std::string(PC_EVENT_NOTIFYFAIL), std::string(""));
	}
	else
	{
		Net::getInstance()->pushMsg(std::string(event), std::string(""));
	}
	json_t *msg = req->msg;
	json_decref(msg);
	pc_notify_destroy(req);
}

void Net::pomeloRequestCallBack(pc_request_t *req, int status, json_t *resp)
{
	auto event = req->route;
	if(status == -1)
	{
		Net::getInstance()->pushMsg(std::string(event), std::string("{\"error\":true}"));
		Net::getInstance()->pushMsg(std::string(PC_EVENT_REQUESTFAIL), std::string(""));
	}
	else if(status == 0) 
	{

		auto msg = json_dumps(resp, 0);
		Net::getInstance()->pushMsg(std::string(event), std::string(msg));
		free(msg);
	}
	json_t *msg = req->msg;
	json_decref(msg);
	pc_request_destroy(req);
}

void Net::pomeloMsgCallBack(pc_client_t *client, const char *event, void *data)
{
	char nullStr[] = "";
	void *msg = data ? data : (void*)nullStr;
	if(data)
	{
		msg = json_dumps((const json_t*)data, 0);
	}

	Net::getInstance()->pushMsg(std::string(event), std::string((const char*)msg));
	if(data)
	{
		free(msg);
	}
}
