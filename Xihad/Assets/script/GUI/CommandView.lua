local Window = require 'GUI.Window'
local GUIController = require 'ui.GUIController'
local CommandView = {
	skillEntry= '技能',
	itemEntry = '道具',
	swapEntry = '交换',
	stdbyEntry= '待机',
}

function CommandView._addEntry(viewData, name, hover, disabled)
	local entry = {
		name = CommandView[name],
		hover = hover or false,
		disabled = disabled or false,
	}
	
	table.insert(viewData, entry)
	return entry
end

function CommandView._createSkillList(skillCaster)
	local list = {}
	for skill, rest in skillCaster:allSkills() do
		table.insert(list, {
				name = skill:getName(),
				value = rest,
				disabled = not skillCaster:canCast(skill),
			})
	end
	
	return list
end

function CommandView._createItemList(parcel)
	return {}
	-- local list = {}
	-- for item, count in parcel:allItems() do
	-- 	table.insert(list, {
	-- 			name = item:getName(),
	-- 			value = count,
	-- 			disabled = not parcel:canUse(item),
	-- 		})
	-- end
	
	-- return list
end

function CommandView.setListener(listener)
	-- GUIController:subscribeEvent('Command.Hover', function ()
		
	-- end)
	
	-- GUIController:subscribeEvent('Command.Select', function ()
		
	-- end)
end

function CommandView.setList(entry, list)
	entry.list = list
	
	if #list == 0 then
		entry.disabled = true
	end
end

function CommandView.canExchange(warrior)
	return false
end

function CommandView.show(warrior, x, y)
	local viewData = {}
	
	local skillEntry= CommandView._addEntry(viewData, 'skillEntry', true)
	local skillList = CommandView._createSkillList(warrior:findPeer(c'SkillCaster'))
	CommandView.setList(skillEntry, skillList)
	
	local itemEntry= CommandView._addEntry(viewData, 'itemEntry')
	local itemList = CommandView._createItemList(warrior:findPeer(c'Parcel'))
	CommandView.setList(itemEntry, itemList)
	
	local canExchange = CommandView.canExchange(warrior)
	CommandView._addEntry(viewData, 'swapEntry', nil, not canExchange)
	CommandView._addEntry(viewData, 'stdbyEntry')
	
	local wnd = GUIController:showWindow('Command', viewData)
	Window.setPosition(wnd, x, y)
	return wnd
end

function CommandView.close()
	GUIController:hideWindow('Command')
end

return CommandView
