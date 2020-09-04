function setup(core)
	size_ = Vector2u()
	size_.x = 100 
	size_.y = 200
	core:setParam("window_size", size_)

	size = core:getParam("window_size")
	print(size.x)
	print(size.y)
end