#ifndef UML_MODEL
#define UML_MODEL

#include <list>
#include "UMLClass.h"
#include "UMLRelationship.h"
#include "ClassField.h"
#include "ClassMethod.h"
#include "MethodParameter.h"
#include <nlohmann/json.hpp>


// So I dont have to type const std::string& all the gdang time :)))
using StrRef = const std::string&;
using json = nlohmann::json;


/*
    The UMLModel will hold all the data for the current running program. It will hold
    all the class, relationship, and attribute data. Other classes can access the data
    indirectly via method calls. 
*/
class UMLModel {
    private:

        // Holds all the existing classes in the current model. 
        // Duplicates should not be allowed in this list.
        // Any insert/deletions to this list should go through the add/remove methods.
        std::list <UMLClass> AllClasses;

        //Contains all current existing relationships
        //Relationship must have name, source, destination
        //No duplicate names allowed
        std::list <UMLRelationship> AllRelationships;

        // Internal method for getting an iterator to the class in the model by name.
        std::list<UMLClass>::iterator get_class_iter_by_name(StrRef className);

        std::list<UMLRelationship>::iterator get_relationship_iter_by_src_and_dest_name(StrRef classSrc, StrRef classDest);

        friend class JSONFileSys;
        
    public:

        UMLModel();
        ~UMLModel();

        #pragma region Model_Class_Operations
        
            // Checks to see if the class name already exists in the model.
            // Returns true if the class exists in the model already, and false otherwise.
            bool does_class_exist(StrRef className);

            // Adds a class froom a new UMLClass object
            // Returns true if add was successful; false if it failed
            bool add_class(UMLClass newClass);

            // Adds a class to the model from a name alone.
            // Returns true if the add was successful, false if it failed.
            bool add_class(StrRef className);

            bool add_class(StrRef className, std::vector<ClassField> fields, std::vector<ClassMethod> methods);

            // Removes a class from the model by name.
            // Returns true if the removal was successful, false otherwise.
            bool remove_class(StrRef className);

            // Modify a class name from the nameFrom parameter to the nameTo parameter.
            // Returns false in cases where either the nameFrom doesnt exist or the
            // nameTo is not a valid name. Returns true if the modify was successful.
            bool modify_class_name(StrRef nameFrom, StrRef nameTo);

            // Gets a copy of the class specified by name and puts it into the outClass variable
            // Returns true if the class exists, false otherwise
            // NOTE: modifying the contents of outClass does not modify the contents of the model.
            bool get_class_by_name(StrRef className, UMLClass& outClass);

            // Returns a string list that contains all the current classes in the model.
            const std::list <std::string> get_all_class_names();

            const std::list<UMLClass> get_all_classes() const;

        #pragma endregion Model_Class_Operations

        #pragma region Model_Relationship_Operations

            //Checks if relationship with name already exists
            bool does_relationship_exist(StrRef classSrc, StrRef classDest);

            bool add_relationship(StrRef classSrc, StrRef classDest, RelationshipType type);

            bool remove_relationship(StrRef classSrc, StrRef classDest);

            //Checks that class exists
            //Returns list of relationships where className is either its source or destination
            const std::list <UMLRelationship> get_class_relationships(StrRef className);

            //Returns list of all current existing and valid relationships.
            const std::list <UMLRelationship> get_all_relationships() const;

            //Called when a class is deleted
            //Checks if class being deleted is either a source or destination of a relationship
            //If so, relationship is also deleted because relationshp cannot exist without source AND destination.
            void ensure_relationship_delete(StrRef className);
        
            // Gets a copy of the relationship specified by name and puts it into the outRelationship variable
            // Returns true if the relationship exists, false otherwise
            // NOTE: modifying the contents of outRelationship does not modify the contents of the model.
            bool get_relationship_by_src_and_dest(StrRef classSrc, StrRef classDest, UMLRelationship& outRelationship);

        #pragma endregion Model_Relationship_Operations

        #pragma region Class_Fields

            // Adds a field to specified class
            // Returns true if the add was a success
            // Fails if either the class is not in the model or the class rejects the field
            bool add_class_field(StrRef className, ClassField field);

            // Removes a field by name from a specified class
            // Returns true if remove was a success
            // Fails if either the class is not in the model or the field is not in the class
            bool remove_class_field(StrRef className, StrRef fieldName);

            // Rename a field under className from fieldNameFrom to fieldNameTo
            // Returns true if rename was a success
            // Returns false if the className is not in the model, or the class rejects either the fieldNameFrom or fieldNameTo
            bool rename_class_field(StrRef className, StrRef fieldNameFrom, StrRef fieldNameTo);
        
            // Sees if a class has a specified field
            // Returns true if the class has the field
            // Returns false if either the class doesn't exist or the field is not on the class
            bool does_class_have_field(StrRef className, StrRef fieldName);

        #pragma endregion Class_Fields

        #pragma region Class_Methods

            // Adds a method to a specified class. Returns true if the add was successful.
            // Returns false if either the class doesn't exist or the class rejected the method for
            // any reason (ie, duplicate method names)
            bool add_class_method(StrRef className, ClassMethod method);

            // Removes a method from a specified class. Returns true if the removal was successful.
            // Returns false if either the class doesn't exist or the class didn't have a method
            // by the name passed in
            bool remove_class_method(StrRef className, StrRef methodName);

            // Renames a method from a specified class. Returns true if the rename was successful.
            // Returns false if the class doesnt exist, the methodNameFrom doesn't exist, or the
            // methodNameTo already exists
            bool rename_class_method(StrRef className, StrRef methodNameFrom, StrRef methodNameTo);

            // Checks if the specified class has the specified method name.
            // Returns true if that's the case. False if the class doesn't exist
            // or the method name doesn't exist within the class.
            bool does_class_have_method(StrRef className, StrRef methodName);

        #pragma endregion Class_Methods

        #pragma region Class_Method_Parameters

            // Adds a parameter to a method that is contained within a class (whew!)
            // Returns true if the parameter addition was a success.
            // Returns false if:
            //      1. className doesn't exist
            //      2. methodName doesn't exist within className 
            //      3. the method object rejected the parameter object for any reason
            bool add_class_method_parameter(StrRef className, StrRef methodName, MethodParameter parameter);

            // Removes a parameter from a method that is contained within a class
            // Returns true if the parameter removal was a success.
            // Returns false if:
            //      1. className doesn't exist
            //      2. methodName doesn't exist within className 
            //      3. parameterName doesn't exist within the methodName
            bool remove_class_method_parameter(StrRef className, StrRef methodName, StrRef parameterName);

            // Renames a parameter from the method that is contained within a class
            // Returns true if the parameter rename was successful
            // Returns false if:
            //      1. className doesn't exist
            //      2. methodName doesn't exist within className
            //      3. parameterNameFrom doesn't exist within the methodName
            //      4. parameterNameTo DOES exist within the methodName 
            bool rename_class_method_parameter(StrRef className, StrRef methodName, StrRef paramNameFrom, StrRef paramNameTo);
        
            // Checks if a parameter exists within a method that is contained within a class
            // Returns true if thats the case
            // False otherwise
            bool does_class_method_have_parameter(StrRef className, StrRef methodName, StrRef parameterName);

        #pragma endregion Class_Method_Parameters

        #pragma region Model_JSON

            // Saves the current model to a json file, "fileName.json"
            // 
            // NOTE: currently does not throw exceptions, but in the future it may need to.
            void save_model_to_json(std::string fileName);

            // Loads the current model from a json file, "fileName.json"
            // Returns false either if the filename doesnt exist or the model trying to be 
            // loaded is not valid
            //
            // NOTE: In the future this may simply throw custom exceptions.
            bool load_model_from_json(std::string fileName);

        #pragma endregion Model_JSON
};

void to_json(json& j, const UMLModel& uc);

#endif