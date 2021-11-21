const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
    <title>ESP8266 WiFi Car</title>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <TITLE>My first web page</TITLE>
      <style>
        body {text-align: center;}
        .wrapper {
          width: 360px;
          padding: 16px;
          margin: 16px auto;
          border:1px solid green;
          border-radius: 6px;
         }
         iframe {
            overflow: hidden;
            pointer-events: none;
            background-color: #F7BE81;
            color: white;
          }
          button{
            padding: 8px;
          }
      </style>
  </HEAD>
<BODY>
    <div align="center">
    <h1>ESP8266 WiFi Car</h1>
    <h2>Press "stop" after the server has been reset</h2>
    <br>
    <form method="GET">
        <input type="button" value="Go forward" onclick="window.location.href='forward'">
        <br><br>
        <input type="button" value="Go backward" onclick="window.location.href='backward'">
         <br><br>
        <input type="button" value="Turn left" onclick="window.location.href='left'">
        <br><br>
        <input type="button" value="Turn right" onclick="window.location.href='right'">
        <br><br>
        <input type="button" value="Car stop" onclick="window.location.href='stop'">
    </form>
    </div>
</BODY>
</HTML>
)=====";
