#include <pch.h>

class gameobject{
public:
    gameobject() {}
    
    virtual void event_input(int event_type, SDL_Event event) { }

    virtual void add_keymap(std::string name, std::vector<int> event){
        if (this->keymap.find(name) != this->keymap.end()){
            this->keymap[name] = event;
            return;
        }

        this->keymap.emplace(name, event);
    }

    virtual bool assert_key(std::string name, int key) {
        if (this->keymap.find(name) == this->keymap.end())
            return false;
        
        std::vector<int> keys = this->keymap[name];

        for (auto& ckey : keys)
            if (ckey == key)
                return true;
                
        return false;
    }

    std::unordered_map<std::string, std::vector<int>> keymap {};
    std::string tag;

    color4 col;

    transform Transform;
    bound Bounds;
};