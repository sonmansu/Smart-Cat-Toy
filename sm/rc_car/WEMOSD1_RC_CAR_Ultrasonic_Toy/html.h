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

        .carButton {
            width: 100;
            height: 100;
            font-size: 100px;
        }

    </style>
</HEAD>
<BODY>
<div align="center">
    <h1>ESP8266 WiFi Car</h1>
    <h2>Press "stop" after the server has been reset</h2>
    <br>

    <form method="GET">
        <!--        https://www.hackster.io/gungoryalcin68/wifi-robot-car-rc-car-nodemcu-web-server-e8c202-->
        <table>
            <tr>
                <td><p><input type="button" class="carButton" value="\" onclick="window.location.href='forward'"></p>
                <td><p><input type="button" class="carButton" value="^" onclick="window.location.href='forward'"></p>
                <td><p><input type="button" class="carButton" value="/" onclick="window.location.href='backward'"></p>
            <tr>
                <td><p><input type="button" class="carButton" value="<" onclick="window.location.href='left'"></p>
                <td><p><input type="button" class="carButton" value="O" onclick="window.location.href='stop'"></p>
                <td><p><input type="button" class="carButton" value=">" onclick="window.location.href='right'"></p>
            <tr>
                <td><p><input type="button" class="carButton" value="/" onclick="window.location.href='backward'"></p>
                <td><p><input type="button" class="carButton" value="v" onclick="window.location.href='backward'"></p>
                <td><p><input type="button" class="carButton" value="\" onclick="window.location.href='backward'"></p>
        </table>
        <br>
        <input type="button" value="Obstacle drive" onclick="window.location.href='obstacle'">
    </form>
    <br>

    <!--    ?????????-->
    <p><button onclick="toyButtonOnClick()" id="toyButton" value = "0">????????????</button></p>
    <p><input type="range" onchange="updateSliderDelay(this)" id="toyDelaySlider" disabled="true" min="300" max="900" step="100" value="400" class="slider"></p>
    <p>?????????: <span id="textSliderValue">400</span></p>
    <br>
    <!-- ????????????-->
    <p><button onclick="doorButtonOnClick()" id="doorButton" value = "0">????????????</button></p>

    <script>
<!--          ?????????-->
          function updateSliderDelay(element) {
            var sliderValue = document.getElementById("toyDelaySlider").value;
            if (sliderValue == "900")
              document.getElementById("textSliderValue").innerHTML = "??????";
            else
              document.getElementById("textSliderValue").innerHTML = sliderValue;
            console.log(sliderValue);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/slider?value="+sliderValue, true);
            xhr.send();
          }
          function toyButtonOnClick() {
            var toy = document.getElementById("toyButton");
            if ( document.getElementById("toyButton").value === "0") {
                document.getElementById("toyDelaySlider").disabled = false;
                // flagToy = "1" //????????? ?????? ?????? ????????????
                document.getElementById("toyButton").value = "1";
                toy.innerHTML = "?????????"
                toy.style.background = "red"
            } else {
                document.getElementById("toyDelaySlider").disabled = true;
                document.getElementById("toyButton").value = "0";
                toy.innerHTML = "????????????"
                toy.style.background = "white"
            }
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "toyButton?value="+document.getElementById("toyButton").value, true);
            xhr.send();
          }
<!--          ????????????-->
          function doorButtonOnClick() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "doorButton", true);
            xhr.send();
          }
        </script>
    


</div>
</BODY>
</HTML>
)=====";
