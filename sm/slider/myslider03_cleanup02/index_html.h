const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    /*.slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;*/
    /*  outline: none; -webkit-transition: .2s; transition: opacity .2s;}*/
    /*.slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}*/
    /*.slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; }*/
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p><button onclick="toyButtonOnClick()" id="toyButton" value = "0">놀아주기</button></p>
  <p>딜레이: <span id="textSliderValue">400</span></p>
  <p><input type="range" onchange="updateSliderDelay(this)" id="toyDelaySlider" disabled="true" min="300" max="900" step="100" value="400" class="slider"></p>
<script>
  function updateSliderDelay(element) {
    var sliderValue = document.getElementById("toyDelaySlider").value;
    if (sliderValue == "900")
      document.getElementById("textSliderValue").innerHTML = "랜덤";
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
        // flagToy = "1" //이렇게 하면 값이 안바뀌네
        document.getElementById("toyButton").value = "1";
        toy.innerHTML = "멈추기"
        toy.style.background = "red"
    } else {
        document.getElementById("toyDelaySlider").disabled = true;
        document.getElementById("toyButton").value = "0";
        toy.innerHTML = "놀아주기"
        toy.style.background = "white"
    }
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "servoButton?value="+document.getElementById("toyButton").value, true);
    xhr.send();

  }
</script>
</body>
</html>
)rawliteral";
