const textElement = document.getElementById('textarea');
const getButton = document.getElementById('getdata');
getButton.onclick = getAllUMLData;
const UMLURL = 'http://localhost:8080';

let classes = [];
let relationships = [];

var HttpClient = function() {
    this.get = function(aUrl, aCallback) {
        var anHttpRequest = new XMLHttpRequest();
        anHttpRequest.onreadystatechange = function() { 
            if (anHttpRequest.readyState == 4 && anHttpRequest.status == 200)
                aCallback(anHttpRequest.responseText);
        }

        anHttpRequest.open( "GET", aUrl, true );            
        anHttpRequest.send( null );
    }
}

function getAllUMLData() {
    let client = new HttpClient();
    client.get(UMLURL + '/data', function(response) {
        let objectReponse = JSON.parse(response);
        classes = objectReponse.classes;
        relationships = objectReponse.relationships;
        generateAllClassDivs();
    });
}

function generateAllClassDivs() {
    classes.forEach(element => {
        let className = element.name;
        let fields = element.fields;
        let methods = element.methods;
        generateSingleClassDiv(className, fields, methods);
    });
}

function generateSingleClassDiv(className, fields, methods) {
    var classDiv = document.createElement("div");
    classDiv.setAttribute("id", className);
    classDiv.setAttribute("class", "class-div");

    var classHeaderDiv = document.createElement("div");
    classHeaderDiv.setAttribute("class", "class-divheader");
    classHeaderDiv.innerHTML = className;
    classDiv.appendChild(classHeaderDiv);

    document.body.appendChild(classDiv);
}
