#include "UMLModel.h"
#include "JSONFileSys.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using StrRef = const std::string&;

UMLModel::UMLModel() {}

UMLModel::~UMLModel(){}

std::list<UMLClass>::iterator UMLModel::get_class_iter_by_name(StrRef className)
{
    if(AllClasses.empty())
        return AllClasses.end();

    for(auto iter = AllClasses.begin(); iter != AllClasses.end(); iter++)
    {
        if((*iter).get_class_name() == className)
            return iter;
    }

    return AllClasses.end();
}

std::list<UMLRelationship>::iterator UMLModel::get_relationship_iter_by_src_and_dest_name(StrRef classSrc, StrRef classDest)
{
    if (AllRelationships.empty())
    {
        return AllRelationships.end();
    }

    for (auto i = AllRelationships.begin(); i != AllRelationships.end(); i++)
    {
        if ((*i).get_src_class().get_class_name() == classSrc
            && (*i).get_dest_class().get_class_name() == classDest)
        {
            return i;
        }
    }

    return AllRelationships.end();
}

#pragma region Model_Class_Operations

    bool UMLModel::does_class_exist(StrRef className)
    {
        return get_class_iter_by_name(className) != AllClasses.end();
    }

    bool UMLModel::add_class(UMLClass newClass)
    {
        if(does_class_exist(newClass.get_class_name()))
        {
            return false;
        }
        else
        {
            AllClasses.push_back(newClass);
            return true;
        }
    }

    bool UMLModel::add_class(StrRef className)
    {
        if(does_class_exist(className))
        {
            return false;
        }
        else
        {
            UMLClass newClass {className};
            AllClasses.push_back(newClass);
            return true;
        }
    }

    bool UMLModel::add_class(StrRef className, std::vector<ClassField> fields, std::vector<ClassMethod> methods)
    {
        if (does_class_exist(className))
        {
            return false;
        }
        else
        {
            UMLClass newClass { className, fields, methods };
            AllClasses.push_back(newClass);
            return true;
        }
    }

    bool UMLModel::remove_class(StrRef className)
    {
        auto iter = get_class_iter_by_name(className);

        if(iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            ensure_relationship_delete(className);
            AllClasses.erase(iter);
            return true;
        }
    }

    bool UMLModel::modify_class_name(StrRef nameFrom, StrRef nameTo)
    {
        // If the name we're modifying to exists already OR the name we're modifying 
        // from doesn't exist, return false
        if(does_class_exist(nameTo) || !does_class_exist(nameFrom))
        {
            return false;
        }
        else
        {
            auto iter = get_class_iter_by_name(nameFrom);
            (*iter).set_class_name(nameTo);
            return true;
        }
    }

    bool UMLModel::get_class_by_name(StrRef className, UMLClass& outClass)
    {
        if (does_class_exist(className))
        {
            outClass = *(get_class_iter_by_name(className));
            return true;
        }
        else
        {
            return false;
        }
    }

    const std::list <std::string> UMLModel::get_all_class_names()
    {
        std::list <std::string> result;

        for (auto c : AllClasses)
        {
            result.push_back(c.get_class_name());
        }

        return result;
    }

    const std::list<UMLClass> UMLModel::get_all_classes() const
    {
        return AllClasses;
    }

#pragma endregion Model_Class_Operations

#pragma region Model_Relationship_Operations

    bool UMLModel::does_relationship_exist(StrRef classSrc, StrRef classDest)
    {
        return get_relationship_iter_by_src_and_dest_name(classSrc, classDest) != AllRelationships.end();
    }

    bool UMLModel::add_relationship(StrRef classSrc, StrRef classDest, RelationshipType type)
    {
        if (does_relationship_exist(classSrc, classDest))
        {
            return false;
        }
        else
        {
            if (does_class_exist(classSrc) && does_class_exist(classDest))
            {
                UMLClass& src = *(get_class_iter_by_name(classSrc));
                UMLClass& dest = *(get_class_iter_by_name(classDest));

                UMLRelationship newRelationship{ src, dest, type };
                AllRelationships.push_back(newRelationship);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool UMLModel::remove_relationship(StrRef classSrc, StrRef classDest)
     {
         auto i = get_relationship_iter_by_src_and_dest_name(classSrc, classDest);
         if (i == AllRelationships.end())
         {
             return false;
         }
         else 
         {
             AllRelationships.erase(i);
             return true;
         }
    }

    const std::list <UMLRelationship> UMLModel::get_class_relationships(StrRef className)
     {
         std::list <UMLRelationship> result;

         if (does_class_exist(className))
         {
             for (auto i = AllRelationships.begin() ; i != AllRelationships.end() ; i++)
             {
                 if ((*i).get_src_class() == className || (*i).get_dest_class() == className)
                 {
                     result.push_back(*i);
                 }
             }
         }
         return result;
    }

    const std::list <UMLRelationship> UMLModel::get_all_relationships() const
    {
        return AllRelationships;
    }

    void UMLModel::ensure_relationship_delete(StrRef className)
    {
        std::list <UMLRelationship> classRelats = get_class_relationships(className);
    
        for (auto i = classRelats.begin() ; i != classRelats.end() ; i++)
        {
            remove_relationship((*i).get_src_class().get_class_name(), (*i).get_dest_class().get_class_name());
        }
    }

    bool UMLModel::get_relationship_by_src_and_dest(StrRef classSrc, StrRef classDest, UMLRelationship& outRelationship)
    {
        if(does_relationship_exist(classSrc, classDest))
        {
            outRelationship = *(get_relationship_iter_by_src_and_dest_name(classSrc, classDest));
            return true;
        }
        else
        {
            return false;
        }
    }

#pragma endregion Model_Relationship_Operations

#pragma region Class_Fields

    bool UMLModel::add_class_field(StrRef className, ClassField field)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).add_field(field);
        }
    }

    bool UMLModel::remove_class_field(StrRef className, StrRef fieldName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).remove_field(fieldName);
        }
    }

    bool UMLModel::rename_class_field(StrRef className, StrRef fieldNameFrom, StrRef fieldNameTo)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).rename_field(fieldNameFrom, fieldNameTo);
        }
    }

    bool UMLModel::does_class_have_field(StrRef className, StrRef fieldName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).does_field_already_exist(fieldName);
        }
    }

#pragma endregion Class_Fields

#pragma region Class_Methods

    bool UMLModel::add_class_method(StrRef className, ClassMethod method)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).add_method(method);
        }
    }

    bool UMLModel::remove_class_method(StrRef className, StrRef methodName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).remove_method(methodName);
        }
    }

    bool UMLModel::rename_class_method(StrRef className, StrRef methodNameFrom, StrRef methodNameTo)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).rename_method(methodNameFrom, methodNameTo);
        }
    }

    bool UMLModel::does_class_have_method(StrRef className, StrRef methodName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).does_method_already_exist(methodName);
        }
    }

#pragma endregion Class_Methods

#pragma region Class_Method_Parameters

    bool UMLModel::add_class_method_parameter(StrRef className, StrRef methodName, MethodParameter parameter)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).add_method_parameter(methodName, parameter);
        }
    }

    bool UMLModel::remove_class_method_parameter(StrRef className, StrRef methodName, StrRef parameterName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).remove_method_parameter(methodName, parameterName);
        }
    }

    bool UMLModel::rename_class_method_parameter(StrRef className, StrRef methodName, StrRef paramNameFrom, StrRef paramNameTo)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).rename_method_parameter(methodName, paramNameFrom, paramNameTo);
        }
    }

    bool UMLModel::does_class_method_have_parameter(StrRef className, StrRef methodName, StrRef parameterName)
    {
        auto iter = get_class_iter_by_name(className);
        if (iter == AllClasses.end())
        {
            return false;
        }
        else
        {
            return (*iter).does_method_parameter_exist(methodName, parameterName);
        }
    }

#pragma endregion Class_Method_Parameters

#pragma region Model_JSON

    void UMLModel::save_model_to_json(std::string fileName)
    {
        JSONFileSys jsonIO;
        jsonIO.save_current_model(fileName, *this);
    }

    bool UMLModel::load_model_from_json(std::string fileName)
    {
        JSONFileSys jsonIO;
        jsonIO.load_current_model(fileName, *this);
        return true;
    }

#pragma endregion Model_JSON

    void to_json(json& j, const UMLModel& uc)
    {
        j["classes"] = uc.get_all_classes();
        j["relationships"] = uc.get_all_relationships();
    }