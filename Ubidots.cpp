#include "Ubidots.h"
#include <stdlib.h>

/**
* Constructor.
*/
Ubidots::Ubidtos(String token)
{
	_token = token;
}
String Ubidots::assemble(String method, String endpoint)
{
	String chain = method + "/api/v1.6/"+endpoint+" HTTP/1.1\nHost: "+base_url+"\nUser-Agent: "+user_agent+"\nX-Auth-Token: "+_token+"\n\n";

}


void Ubidots::start(){
	info = assemble();
	int data = Send;
	
}
void Ubidots::create_datasource(){
	info = assemble();
	int data = Send;

}

void Ubidots::save_value(String varibleName, String varialbeValue) {
	info = assemble();
	int data = Send;

}
void Ubidots::create_variable(){
	info = assemble();
	int data = Send;
}
void Ubidots::save_value(String varibleName, String varialbeValue, String context) {
	info = assemble();
	int data = Send;
}


int Ubidots::Send()
{
	TCPClient client;
	char result[512];
	int i = 0;
	int status = 0;

	if (client.connect("things.ubidots.com", 80)) // Connect to the server
	{
		// phant.post() will return a string formatted as an HTTP POST.
		// It'll include all of the field/data values we added before.
		// Use client.print() to send that string to the server.
		client.print(info);
		//delay(1000);
		// Now we'll do some simple checking to see what (if any) response
		// the server gives us.
		int timeout = 1000;
		while (client.available() || (timeout-- > 0))
		{
			char c = client.read();
			Serial.print(c);	// Print the response for debugging help.
			if (i < 512)
				result[i++] = c; // Add character to response string
			delay(1);
		}
		// Search the response string for "200 OK", if that's found the post
		// succeeded.
		if (strstr(result, "200 OK"))
		{
			status = 1;
		}
		else if (strstr(result, "400 Bad Request"))
		{	// "400 Bad Request" means the Phant POST was formatted incorrectly.
			// This most commonly ocurrs because a field is either missing,
			// duplicated, or misspelled.
			status = 2;
		}
		else
		{
			// Otherwise we got a response we weren't looking for.
			status = 3;
		}
	}
	else
	{	// If the connection failed:
		status = 4;
	}
	client.stop();	// Close the connection to server.
	return status;
}