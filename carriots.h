/*
 * This function creates the message body
 * and returns it as a String
 * attributeName - name of the attribute
 * value - value of the attribute
 * type - type of the attribute (1-String, 2-Integer, 3-Float)
 */
String messageBody(String attributeName, String value, int type){
  String body = "{\"protocol\":\"v2\",";
  body += "\"checksum\":\"\",";
  body += "\"device\":\"";
  body += DEVICE;
  body += "\",";
  body += "\"at\":\"now\",";
  body += "\"data\":{\"";
  body += attributeName;
  body += "\":";
  switch(type){
    case 1: 
      body += "\"";
      body += value;
      body += "\"";
      break;
    case 2:
      body += value.toInt();
      break;
    case 3:
      body += value.toFloat();
      break;
    default:
      body += value;
  }
  body += "}}\r\n";
  return body;
}
/*
 * This function builds the Request header
 */
String request(String body){
  String header = "POST /streams/ HTTP/1.1\r\n";
  header += "Host: ";
  header += host;
  header += "\r\n";
  header += "Accept: application/json\r\n";
  header += "User-Agent: ";
  header += DEVICE;
  header += "\r\n";
  header += "Content-Type: application/json\r\n";
  header += "Content-Length: ";
  header += body.length();
  header += "\r\n";
  header += "carriots.apikey: ";
  header += APIKEY;
  header += "\r\n";
  return header;
}

/*
 * This function sends the Http request
 * with the data
 */
void httpSend(String header,String body){
  if(client.connect(host,80)){
    client.print(header);
    client.print("\r\n");
    client.println(body);
  }else{
    Serial.println("connection failed");
  }
}

/*
 * This function sends a stream to the carriots server
 * attributeName - A name in "quotes" for the attribute
 * value - A String value for the attribute
 */
void sendStream(String attributeName, String value){
  String json = messageBody(attributeName,value,1);
  String header = request(json);
  Serial.print(header);
  Serial.print("\r\n");
  Serial.println(json); 
  httpSend(header,json);
}
/*
 * This function sends a stream to the carriots server
 * attributeName - A name in "quotes" for the attribute
 * value - An int value for the attribute
 */
void sendStream(String attributeName, int value){
  String json = messageBody(attributeName,String(value),2);
  String header = request(json);
  Serial.print(header);
  Serial.print("\r\n");
  Serial.println(json); 
  httpSend(header,json);
}
/*
 * This function sends a stream to the carriots server
 * attributeName - A name in "quotes" for the attribute
 * value - A float value for the attribute
 */
void sendStream(String attributeName, double value){
  String json = messageBody(attributeName,String(value),3);
  String header = request(json);
  Serial.print(header);
  Serial.print("\r\n");
  Serial.println(json);
  httpSend(header,json);
}




