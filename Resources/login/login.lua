require "scripts.net"
require "scripts.GameScene"

local ip = "223.252.196.133"
local port = 13014

login = {}

function login.login()
	--[[local scene = cc.Scene:create()
	local layer = cc.Layer:create()
	local bg = cc.Sprite:create("res/altas.png")
	bg:setAnchorPoint(cc.p(0,0))
	layer:addChild(bg)

	scene:addChild(layer)
	]]--
	local startScene = require("scripts.StartScene")
	cclog("start connecting...")
	net.connect(ip, port, login.onConnectGateServer)
	cclog("start gaming...")
    cc.Director:getInstance():runWithScene(startScene)
	--[[cc.Director:getInstance():runWithScene(scene)]]--
end

function login.onConnectGateServer()
	local route = "gate.gateHandler.queryEntry"
	local msg = { uid = "luaClientWindows" }
	cclog("start requesting...")
	net.request(route, msg, login.onRequestGateBack)
end

function login.onRequestGateBack(msg)
	cclog("--- host: " .. msg["host"])
	cclog("--- port: " .. msg["port"])
	net.connect(msg["host"], msg["port"], login.onConnectGameServer)
end

function login.onConnectGameServer()
	local route = "connector.entryHandler.entry"
	local username = cc.UserDefault:getInstance():getStringForKey("username")
    if username == "" then
        username = "user"..os.time()
        cc.UserDefault:getInstance():setStringForKey("username", username)
    end
	local msg = { username = username, rid = "111" }
	cclog("Connected! Request")
	net.request(route, msg, login.onRequestGameServerBack)
end

function login.onRequestGameServerBack(msg)
	cclog("[OK]")
	runScene(msg)
end

return login