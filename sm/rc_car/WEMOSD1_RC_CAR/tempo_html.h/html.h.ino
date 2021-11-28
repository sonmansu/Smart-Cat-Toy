const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
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
  <h1>
      <B>ESP8266 Web Server</B>
  </h1> 
  <p>홈오토메이션 관리자 페이지</p>

  <div class="wrapper">
    LED State:<iframe id="ifResult" name="myIframe" width="100%" height="30" frameBorder="0" scrolling="no"></iframe>
    <h3>조명제어</h3>
    <a href="/ledOn" target="myIframe"><button id="ledOn">거실조명 켜기</button></a>
    <a href="/ledOff" target="myIframe"><button id="ledOff">거실조명 끄기</button></a>
  </div>
  <div class="wrapper">
    <h3>TV 제어</h3>
    <button>TV 켜기</button>
    <button>TV 끄기</button>
  </div>
  
  <script>
    
  </script>
</BODY>
</HTML>
)=====";
