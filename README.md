An attempt at a 3D Engine.

# Rendering Example
![Engine Example](https://github.com/user-attachments/assets/07e8e063-786f-40e3-ae88-a65d902d581e)

## Example Code Usage
```cpp
gameobject* obj = new object();
pEngine->create_object(std::string("name"), obj);


// setting scale
obj->Bounds.scale *= {8.f, 1.f, 8.f};

// setting position, grid
obj->Transform.position = {i * (obj->Bounds.scale.x * 2.f), -4.f, z * (obj->Bounds.scale.z * 2.f)};

// setting color random.
obj->col = {1 + (rand() % 255), 1 + (rand() % 255), 1 + (rand() % 255)}; // vector4
```


### About this project
I wanted to create a simple software / cpu rendering engine that didnt use any GPU calls, I used a lot of resorces creating it, visiting multiple different blogs and sites.
most likely wont ever get anymore updates, and super unoptimized.
