class UMLClass {
    constructor(name, fields, methods) {
        this.name = name;
        this.fields = fields;
        this.methods = methods;
    }
}

class UMLRelationship {
    constructor(src, dest, type) {
        this.src = src;
        this.dest = dest;
        this.type = type;
    }
}

class ClassField {
    constructor(name) {
        this.name = name;
    }
}

class ClassMethod {
    constructor(name, parameters) {
        this.name = name;
        this.parameters = parameters;
    }
}

class MethodParameter {
    constructor(name) {
        this.name = name;
    }
}