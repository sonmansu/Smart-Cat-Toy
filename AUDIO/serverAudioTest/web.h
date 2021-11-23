const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>마이크 테스트</title>

    <style>
        #sound-clips button {
            margin-right: 0.5ex;
        }
    </style>
</head>

<body>
    <input type=checkbox id="chk-hear-mic"><label for="chk-hear-mic">마이크 소리 듣기</label>
    <p>
        <button id="record">녹음</button>
        <button id="stop">정지</button>
    </p>    
    <div id="sound-clips"></div>  <!--여기에 clip들 저장-->


    <script>
        const record = document.getElementById("record")
        const stop = document.getElementById("stop")
        const soundClips = document.getElementById("sound-clips")
        const chkHearMic = document.getElementById("chk-hear-mic")

        const audioCtx = new(window.AudioContext || window.webkitAudioContext)() // 오디오 컨텍스트 정의

        const analyser = audioCtx.createAnalyser()

        function makeSound(stream) {
            const source = audioCtx.createMediaStreamSource(stream)

            source.connect(analyser)
            analyser.connect(audioCtx.destination)
        }

        if (navigator.mediaDevices) {
            console.log('getUserMedia supported.')

            const constraints = {
                audio: true
            }
            let chunks = []

            navigator.mediaDevices.getUserMedia(constraints)
                .then(stream => {

                    const mediaRecorder = new MediaRecorder(stream)
                    
                    chkHearMic.onchange = e => {
                        if(e.target.checked == true) {
                            audioCtx.resume()
                            makeSound(stream)
                        } else {
                            audioCtx.suspend()
                        }
                    }
                    
                    record.onclick = () => {
                        mediaRecorder.start()
                        console.log(mediaRecorder.state)
                        console.log("recorder started")
                        record.style.background = "red"
                        record.style.color = "black"
                    }

                    stop.onclick = () => {
                        mediaRecorder.stop()
                        console.log(mediaRecorder.state)
                        console.log("recorder stopped")
                        record.style.background = ""
                        record.style.color = ""
                    }

                    mediaRecorder.onstop = e => {
                        console.log("data available after MediaRecorder.stop() called.");

                        const clipName = prompt("오디오 파일 제목을 입력하세요.");

                        const clipContainer = document.createElement('article');
                        const clipLabel = document.createElement('p');
                        const audio = document.createElement('audio');
                        const deleteButton = document.createElement('button');
                        const sendButton = document.createElement('button');

                        clipContainer.classList.add('clip');
                        audio.setAttribute('controls', '');
                        deleteButton.innerHTML = "삭제";
                        sendButton.innerHTML = "보내기";
                        clipLabel.innerHTML = clipName;

                        clipContainer.appendChild(audio);
                        clipContainer.appendChild(clipLabel);
                        clipContainer.appendChild(deleteButton);
                        clipContainer.appendChild(sendButton);
                        soundClips.appendChild(clipContainer);

                        audio.controls = true
                        const blob = new Blob(chunks, {
                            'type': 'audio/mp3 codecs=opus'
                        })
                        chunks = [];
                        const audioURL = URL.createObjectURL(blob)
                        audio.src = audioURL
                        console.log("recorder stopped")

                        deleteButton.onclick = e => {
                            evtTgt = e.target
                            evtTgt.parentNode.parentNode.removeChild(evtTgt.parentNode)
                        }
                        sendButton.onclick = e => {

                        }
                    }

                    mediaRecorder.ondataavailable = e => {
                        chunks.push(e.data)
                    }
                })
                .catch(err => {
                    console.log('The following error occurred: ' + err)
                })
        }
    </script>
</body>
</html>
)=====";
