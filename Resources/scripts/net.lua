require "json"

net = {
	onceCallMap = nil,
	listenerMap = nil,

	connected = "connected",
	beKicked = "onKick",
	timeout = "timeout",	
	disconnect = "disconnect",
	connectFail = "connectFailed",
	notifyError = "notifyError",
	notifyFail = "notifyFailed",
	notifySuccess = "notifySuccess",
	invalidRequest = "requestError",
	requestFail = "requestFailed",

	none = 0,
	onGate = 1,
	onConnector = 2,
	state = 0,
}

net.stateMap = {
	connected = 1,
	onKick = 2,
	timeout = 3,	
	disconnect = 4,
	connectFailed = 5,
	notifyError = 6,
	notifyFailed = 7,
	notifySuccess = 8,
	requestError = 9,
	requestFailed = 10,
}

function net.stateHandler(event)
	if("connected" == event)then
		if("function" == type(net.stateMap[event]))then
			net.stateMap[event]()
		end
	elseif("onKick" == event)then

	elseif("timeout" == event)then

	elseif("disconnect" == event)then

	elseif("connectFailed" == event)then

	elseif("notifyError" == event)then

	elseif("notifyFailed" == event)then

	elseif("notifySuccess" == event)then

	elseif("requestError" == event)then

	elseif("requestFailed" == event)then

	end
end

function net.init()
	net.state = net.none
	net.onceCallMap = {}
	net.listenerMap = {}

	Net:getInstance():registerOnMsgLuaCallBack(net.onMessage)
end

function net.onMessage(event, msg)
	--cclog(msg)
	if((type(msg) == "string") and (string.len(msg) > 0))then
		msg = json.decode(msg)
	else
		msg = {}
	end

	if(net.listenerMap[event])then
		net.listenerMap[event](msg)
	elseif(net.onceCallMap[event])then
		net.onceCallMap[event](msg)
		net.onceCallMap[event] = nil
	elseif(net.stateMap[event])then
		net.stateHandler(event)
	end
end

function net.connect(ip, port, callback)
	net.stateMap["connected"] = callback
	Net:getInstance():connect(tostring(ip), tonumber(port))
end

function net.request(route, msg, callback)
	net.onceCallMap[route] = callback
	Net:getInstance():pomeloRequest(tostring(route), tostring(json.encode(msg)))
end

function net.notify(route, msg, callback)
	net.onceCallMap[route] = callback
	Net:getInstance():pomeloNotify(tostring(route), tostring(json.encode(msg)))
end

function net.addListener(event, callback)
	net.listenerMap[event] = callback
	Net:getInstance():addListener(tostring(event))
end
function net.removeListener(event)
	Net:getInstance():removeListener(tostring(event))
	net.listenerMap[event] = nil
end

function net.httpRequest(url, callback)
	Net:getInstance():httpRequest(url, callback);
end

--[[ net state callbacks
function net.onKick()
	cclog("--- be kicked ---")
end

function net.onTimeout()
	cclog("--- timeout ---")
end

function net.onDisconnect()
	cclog("--- disconnect ---")
end

function net.onConnectFail()
	cclog("--- connect fail ---")
end

function net.onNotifyError()
	cclog("--- notify error ---")
end

function net.onNotifyFail()
	cclog("--- notify fail ---")
end

function net.onNotifySuccess()
	cclog("--- notify success ---")
end
	
function net.onInvalidRequest()
	cclog("--- invalid request ---")
end

function net.onRequestFail()
	cclog("--- request fail ---")
end
--]]
--[[ example:
function net.testHttpRequest()
	local function httpRequestCallback(isSuccess, value)
		print("---", isSuccess, value)
		cclog("");
	end
	net.httpRequest("http://192.168.2.210/serverlist.txt", httpRequestCallback)
end
--]]