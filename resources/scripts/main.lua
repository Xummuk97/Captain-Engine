rgba = { 0, 0, 0, 0 }

function setup()
	core:loadTexture("test", "test1.png")

	core:spawn("Player", 1)

end

function init(obj)
	if obj:getType() == "Player" then
		obj:setTexture("test")
		obj:setTextureRect(0, 0, 32, 32)
	end
end

function update(obj)
	if obj:getType() == "Player" then
		if core:isKeyPressed(KB_A) then 
			obj:move(-1.0, 0.0)
		elseif core:isKeyPressed(KB_D) then 
			obj:move(1.0, 0.0)
		end
	end
end

function draw(obj)
	if obj:getType() == "Player" then
		obj:drawSprite()
	end
end

function gui()
	ImGui.beginWindow("Test Window")
	ImGui.colorEdit4("Color", rgba)
	ImGui.endWindow()

	print(rgba[1])
end