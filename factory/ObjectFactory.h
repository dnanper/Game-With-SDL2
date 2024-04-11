#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "../object/GameObject.h"
#include <map>
#include <functional>
#include <string>

class ObjectFactory
{
    public:
        GameObject* CreateObject(std::string type, Properties* props);
        void RegisterType(std::string className, std::function<GameObject*(Properties* props)> type);
        static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new ObjectFactory(); }
    
    private:
        ObjectFactory() {}
        static ObjectFactory* s_Instance;
        std::map<std::string, std::function<GameObject*(Properties* props)>> m_TypeRegistry;
};

template<class Type>
class Registrar
{
    public:
        Registrar(std::string className)
        {
            ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* { return new Type(props);});
        }
};

#endif  // GAMEOBJECTFACTORY_H