#include <stdio.h>
#include <stdbool.h>

#include "json_write.h"


// If a string, int float or bool are: 
// *, *, 		they will be printed as normal
// NULL, NULL, 	they will not be printed (invalid)
// *, NULL, 	they will not be printed (invalid)
// NULL, *, 	they will be printed as just the value without a name
// If an array or an object are:
// *, *, 		they will not be printed (invalid)
// NULL, NULL, 	they will simply be an open and closed bracket
// *, NULL, 	they will be printed as a regular array or object with a name
// NULL, *, 	they will not be printed (invalid)

// For primitives, if the value is NULL, the element is invalid
// For containers, if the value is not NULL, the element is invalid

// Possible problem, if we make JSONWriteIndent explicitly necessary, how do we do the opening and closing brackets
// If you want an empty object / array, you would have to do an indent and outdent 
// Whereas with implicit JSONWriteIndent you would only need the JSONWriteOutdent when creating the element
// One problem either way is what happens if you call JSONWriteElement with an array / object and then dont do any indents or outdents at all?
// We could check if the last element in the json.hierarchy was an array / object and if it was correctly escaped (closing bracket)
// If it wasnt then we add '{},' or '[],' to the end of json.contents 


// So, when attempting to call JSONWriteElement, if 'json.previous_token' is an array / object and there is no {}, indicating its empty, we append '{},' or '[],'
// The only way to place an element inside an array / object is to explicitly call 'JSONWriteIndent'
// And then to stop placing inside the array / object you would need to call 'JSONWriteOutdent'

int main(int argc, char *argv[]){
	
	JSONWrite json = JSONWriteNew();

	int age = 19;
	float fl = 0.4;
	bool toggle = false;
	JSONWriteIndent(&json);
		
		JSONWriteElement(&json, JSON_WRITE_TYPE_INT, "age", &age);
		
		JSONWriteElement(&json, JSON_WRITE_TYPE_ARRAY, "colors", NULL);
		JSONWriteIndent(&json);

			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "white");
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, "bleh", "black");
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "blue");
			
			JSONWriteElement(&json, JSON_WRITE_TYPE_ARRAY, "aquamarine", NULL);
			JSONWriteIndent(&json);

				JSONWriteElement(&json, JSON_WRITE_TYPE_FLOAT, NULL, &(fl));
				fl += 0.123;
				JSONWriteElement(&json, JSON_WRITE_TYPE_FLOAT, NULL, &(fl));
				fl += 0.341;
				JSONWriteElement(&json, JSON_WRITE_TYPE_FLOAT, NULL, &(fl));

			JSONWriteOutdent(&json);

			JSONWriteIndent(&json);
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "orange");
			JSONWriteOutdent(&json);

		JSONWriteOutdent(&json);

		JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, "something random", "yup");

		JSONWriteElement(&json, JSON_WRITE_TYPE_OBJECT, "numbers", NULL);
		JSONWriteIndent(&json);

			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "one");
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "two");
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "three");
			JSONWriteElement(&json, JSON_WRITE_TYPE_STRING, NULL, "five");

		JSONWriteOutdent(&json);
		
		JSONWriteElement(&json, JSON_WRITE_TYPE_BOOLEAN, "yeah?", &toggle);
		toggle = !toggle;
		JSONWriteElement(&json, JSON_WRITE_TYPE_BOOLEAN, "im running out of bullshit", &toggle);

	JSONWriteOutdent(&json);

	JSONWriteToFile(&json, "../assets/output.json");

	JSONWriteFree(&json);

	return 0;
}