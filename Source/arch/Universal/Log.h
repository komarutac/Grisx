#pragma once
#define KLog(Format, Format2) ConFormatTo(DefaultConsole, "[%s] " Format "\n", __FUNCTION__, Format2)
#define KDie(Message) ConFormatTo(DefaultConsole, "[%s] Dying now...\n", __FUNCTION__); Die(Message);