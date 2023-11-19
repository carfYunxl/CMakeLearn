#entt Usage
##1 使用构造函数插入组件 emplace
~~~C++
	// 原地构造component， 后面跟构造函数的参数列表
	registry.emplace<Component>(entity, 0., 0.);
	
	//或者默认构造，再赋值
	auto &vel = registry.emplace<velocity>(entity);
	vel.dx = 0.;
	el.dy = 0.;
~~~
	
##2 插入组件 insert
~~~C++
	// default initialized type assigned by copy to all entities
	registry.insert<position>(first, last);

	// user-defined instance assigned by copy to all entities
	registry.insert(from, to, position{0., 0.});
	
	// first and last specify the range of entities, instances points to the first element of the range of components
	registry.insert<position>(first, last, instances);
~~~

	
##3 更新组件 patch & replace
	// replaces the component in-place
	registry.patch<position>(entity, [](auto &pos) { pos.x = pos.y = 0.; });

	// constructs a new instance from a list of arguments and replaces the component
	registry.replace<position>(entity, 0., 0.);

	//当不确定entity是否有某个组件时，可调用emplace_or_replace方法：
	registry.emplace_or_replace<position>(entity, 0., 0.);

##4 all_Of & any_of
~~~C++
	// true if entity has all the given components
	bool all = registry.all_of<position, velocity>(entity);

	// true if entity has at least one of the given components
	bool any = registry.any_of<position, velocity>(entity);
~~~

##5 删除组件
~~~C++
	// 已知entity有某组件，调用erase
	registry.erase<position>(entity);

	// 在不确定是否有某组件时，调用remove
	registry.remove<position>(entity);

	//删除所有entity的某个组件
	registry.clear<position>();

	//或者删除所有entity
	registry.clear();
~~~

##6 获取组件
~~~C++
	const auto &cregistry = registry;

	// const and non-const reference
	const auto &crenderable = cregistry.get<renderable>(entity);
	auto &renderable = registry.get<renderable>(entity);

	// const and non-const references
	const auto [cpos, cvel] = cregistry.get<position, velocity>(entity);
	auto [pos, vel] = registry.get<position, velocity>(entity);
~~~
