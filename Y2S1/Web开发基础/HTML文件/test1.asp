<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>考试系统</title>
    <style>
        body {
            background-color: black;
            color: white;
            font-size: 18px;
            text-align: center;
        }
        h1 {
            font-size: 50px;
        }
        h2 {
            font-size: 40px;
        }
        textarea {
            resize: none;
            width: 300px;
            height: 50px;
            font-size: 25px;
            text-align: center;
            margin-top: 10px;
        }
        #timer {
            height: 50px;
            width: 450px;
            font-size: 25px;
            position: fixed;
            top: 60px;
            left: 100px;
        }
        #Hello {
            font-size: 30px;
        }
        #examContainer {
            margin: 0 auto;
            width: 80%;
            padding: 20px;
            border: 1px solid white;
        }
        #endDisplay {
            margin: 0 auto;
            width: 80%;
            padding: 20px;
            border: 1px solid white;
        }
        #startButton {
            background-color: green;
            color: white;
            padding: 10px 20px;
            font-size: 16px;
            cursor: pointer;
        }
        #submitButton {
            background-color: blue;
            color: white;
            padding: 10px 20px;
            font-size: 16px;
            cursor: pointer;
        }
        #questionImg1 {
            display: block;
            width: 300px;
            height: 200px;
            margin: 0 auto;
        }
        #questionImg2 {
            display: block;
            width: 300px;
            height: 300px;
            margin: 0 auto;
        }
        #questionImg3 {
            display: block;
            width: 300px;
            height: 150px;
            margin: 0 auto;
        }
        #questionImg4 {
            display: block;
            width: 300px;
            height: 200px;
            margin: 0 auto;
        }
        #questionImg5 {
            display: block;
            width: 300px;
            height: 400px;
            margin: 0 auto;
        }
        #questionImg6 {
            display: block;
            width: 300px;
            height: 400px;
            margin: 0 auto;
        }
        #questionImg7 {
            display: block;
            width: 300px;
            height: 200px;
            margin: 0 auto;
        }
        #questionContainer p {
            font-size: 25px;
        }
        #usedTime {
            font-size: 30px;
        }
        #score {
            font-size: 50px;
            font-family: 'Times New Roman', Times, serif;
        }
        #incorrectAnswers {
            font-size: 30px;
        }
    </style>
</head>
<body>
    <%
        
    Set conn = Server.CreateObject("ADODB.Connection")
    conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\inetpub\wwwroot\MyWeb\score.mdb"

    Set rs = Server.CreateObject("ADODB.Recordset")
    rs.Open "SELECT s_name, s_score FROM score ORDER BY s_score DESC", conn

    %>
    <script>
        var userAnswers = {};
        var incorrectAnswers = {};
        var isSubmitted = false;
        var timeStart;
        var time;
        var countdown = 300;
        var minutes;
        var seconds;
        var score = 0;
        var incorrectAmount = 0;

        function displayHello() {
            var username = document.getElementById("username").value;
            var now = new Date();
            var hours = now.getHours();
            var hello = "";

            if (hours >= 6 && hours < 12) {
                hello = "早上好，" + username + " 考生";
            }
            else if (hours >= 12 && hours < 18) {
                hello = "下午好，" + username + " 考生";
            }
            else{
                hello = "晚上好，" + username + " 考生";
            }
            document.getElementById("Hello").innerHTML = hello;
        }

        function startTimer() {
            timeStart = new Date();
            time = setInterval(updateTimer, 1000);
            displayTime();
        }

        
        function displayTime() {
            var minutesRemaining = Math.floor(countdown / 60);
            var secondsRemaining = countdown % 60;
            
            document.getElementById("timer").innerHTML = "剩余时间: " + minutesRemaining + " 分 " + secondsRemaining + " 秒";

            if (countdown === 0) {
                endExam(); // 自动提交考试
            } else {
                countdown--; // 每秒减一
                setTimeout(displayTime, 1000); // 每隔一秒更新显示
            }
        }

        function updateTimer() {
            var currentTime = new Date();
            var timeDiff = currentTime - timeStart;
            seconds = Math.floor(timeDiff / 1000);
            minutes = Math.floor(seconds / 60);
            seconds = seconds % 60;
         
        }

        function startExam() {
            var username = document.getElementById("username").value;
            var rule = document.getElementById("readRules").checked;
            var blankCnt = 0;

            for (let i = 0; i < username.length; i++) {
                if (username[i] == ' ') {
                    blankCnt++;
                }
            }
            if (blankCnt == username.length && username) {
                alert("请不要输入空白名！");
            }
            else if (rule && username) {
                document.getElementById("startDisplay").style.display = "none";
                document.getElementById("startDisplay2").style.display = "none";
                document.getElementById("timer").style.display = "block";
                document.getElementById("questionContainer").style.display = "block";
                document.getElementById("submitButton").style.display = "block";
                
                
                
                displayHello();
                startTimer();
            }
            else if (username) {
                alert("请阅读并同意考试规则才可开始考试！");
            }
            else if (rule) {
                alert("请填写用户名再开始考试！");
            }
            else {
                alert("请填写用户名并阅读同意考试规则才可开始考试！");
            }
        }

        function endExam() {
            var username = document.getElementById("username").value;
            document.getElementById("examContainer").style.display = "none";
            
            calculateScore();

            // 提交表单数据到 process_form.asp，包括分数
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "process_form.asp", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    // 跳转到考试结束页面
                    window.location.href = "test1.asp";
                }
            };

            // 将分数添加到表单数据中
            xhr.send("username=" + encodeURIComponent(username) + "&score=" + score);
            
            
            document.getElementById("endDisplay").style.display = "block";
            document.getElementById("user").innerHTML = "恭喜您完成了考试，" + username + " 考生!";
            document.getElementById("usedTime").innerHTML = "用时: " + minutes + " 分 " + seconds + " 秒";
            document.getElementById("score").innerHTML = "得分：" + score + " %";

            if (score > 50){
                alert("恭喜，你获得的分数是" + score + "分!");
            }
            else{
                alert("很遗憾，你只获得了"+ score + "分，再接再厉...")
            }

        }

        function calculateScore() {
            var isCorrect = 1;
            var correctAnswer = [
                {
                    answer: "B"
                },
                {
                    answer: "C"
                },
                {
                    answer: "D"
                },
                {
                    answer: "B"
                },
                {
                    answer: "A"
                },
                {
                    answer: ["A", "B", "D"]
                },
                {
                    answer: ["B", "C", "D"]
                },
                {
                    answer: ["A", "C"]
                },
                {
                    answer: "堀与宫村"
                },
                {
                    answer: "达尔文游戏"
                }
            ]

            for (let i = 1; i < 6; i++) {
                userAnswers = document.getElementsByName("q" + i);
                for (let j = 0; j < 4; j++) {
                    if (userAnswers[j].checked) {
                        if (userAnswers[j].value == correctAnswer[i - 1].answer[0]) {
                            score++;
                        }
                        else {
                            incorrectAnswers[incorrectAmount++] = document.getElementById("Question" + i);
                        }
                    }
                }
            }
            for (let i = 6; i < 9; i++) {
                var cnt = 0, pre = 0;
                isCorrect = 1;
                userAnswers = document.getElementsByName("q" + i);
                for (let j = 0; j < 4; j++) {
                    pre = cnt;
                    if (userAnswers[j].checked) {
                        for (let k = 0; k < correctAnswer[i - 1].answer.length; k++) {
                            if (userAnswers[j].value == correctAnswer[i - 1].answer[k]) {
                                cnt++;
                            }
                        }
                        if (pre == cnt) {
                            isCorrect = 0;
                        }
                    }
                }
                if (cnt == correctAnswer[i - 1].answer.length && isCorrect) {
                    score++;
                }
            }
            for (let i = 9; i < 11; i++) {
                var cnt = 0;
                var cntBlank = 0;
                userAnswers = document.getElementById("q" + i).value;
                for (let j = 0; j < correctAnswer[i - 1].answer.length; j++) {
                    if (userAnswers[j] == correctAnswer[i - 1].answer[j]) {
                        cnt++;
                    }
            
                }
                if (cnt == correctAnswer[i - 1].answer.length && userAnswers.length - cntBlank == correctAnswer[i - 1].answer.length) {
                    score++;
                }
            }
            score *= 10;
        }
    </script>
    <div id="examContainer">
        <h1>考试系统</h1>
        <div id="startDisplay">

            <label for="username">用户名：</label>
            <input type="text" id="username" name="username" required><br><br>
            <input type="checkbox" id="readRules" required>
            <label for="readRules">我已阅读并同意<a href="./ExamRules.html" target="_blank">考试规则</a></label><br><br>
            <button type="button" id="startButton" onclick="startExam()">开始考试</button>

        </div>
        
        <div id="Hello"></div>
        <div id="timer" style="display: none;"></div>
        <div id="questionContainer" style="display: none;">
            <h2>动漫题</h2>
            <div id="question1">
                <p id="Question1">1. 请问下列哪一部动画作品不是出自于京阿尼（京都动画）？</p>
                <label><input type="radio" name="q1" value="A">A. 中二病也要谈恋爱</label>
                <label><input type="radio" name="q1" value="B">B. 进击的巨人</label>
                <label><input type="radio" name="q1" value="C">C. 冰菓</label>
                <label><input type="radio" name="q1" value="D">D. 轻音少女</label>
            </div>
            <div id="question2">
                <p id="Question2">2. 请问下列哪一部动画作品不是出自于飞碟社（Ufotable） ？</p>
                <label><input type="radio" name="q2" value="A">A. Fate</label>
                <label><input type="radio" name="q2" value="B">B. 噬神者</label>
                <label><input type="radio" name="q2" value="C">C. 一拳超人</label>
                <label><input type="radio" name="q2" value="D">D. 鬼灭之刃</label>
            </div>
            <div id="question3">
                <p id="Question3">3. 请问下列哪一部作品不是出自于 MAPPA ？</p>
                <label><input type="radio" name="q3" value="A">A. 狂赌之渊</label>
                <label><input type="radio" name="q3" value="B">B. 咒术回战</label>
                <label><input type="radio" name="q3" value="C">C. 链锯人</label>
                <label><input type="radio" name="q3" value="D">D. 声之形</label>
            </div>
            <div id="question4">
                <p id="Question4">4. 请问下图中的画面出自哪一部动漫？</p>
                <img id="questionImg1" src="./素材/动漫1.jfif" alt="图1">
                <label><input type="radio" name="q4" value="A">A. Overlord</label>
                <label><input type="radio" name="q4" value="B">B. 想要成为影之实力者</label>
                <label><input type="radio" name="q4" value="C">C. 一拳超人</label>
                <label><input type="radio" name="q4" value="D">D. 魔王学院的不适任者</label>
            </div>
            
            <div id="question5">
                <p id="Question5">5. 请问下图中的人物叫什么？</p>
                <img id="questionImg2" src="./素材/人物1.jpg" alt="图2">
                <label><input type="radio" name="q5" value="A">A. 谢斯塔</label>
                <label><input type="radio" name="q5" value="B">B. 鸢一折纸</label>
                <label><input type="radio" name="q5" value="C">C. 伊蕾娜</label>
                <label><input type="radio" name="q5" value="D">D. 锦木千束</label>
            </div>
            <div id="question6">
                <p id="Question6">6. 请选出属于下图中的动漫的人物（答案可能不止一个）</p>
                <img id="questionImg3" src="./素材/动漫2.jfif" alt="图3">
                <label><input type="checkbox" name="q6" value="A">A. 五河琴里</label>
                <label><input type="checkbox" name="q6" value="B">B. 时崎狂三</label>
                <label><input type="checkbox" name="q6" value="C">C. 蕾姆</label>
                <label><input type="checkbox" name="q6" value="D">D. 鸢一折纸</label>
            </div>
            <div id="question7">
                <p id="Question7">7. 请选出属于下图中的动漫的人物（答案可能不止一个）</p>
                <img id="questionImg4" src="./素材/动漫3.jpg" alt="图4">
                <label><input type="checkbox" name="q7" value="A">A. 伊蕾娜</label>
                <label><input type="checkbox" name="q7" value="B">B. 洛琪希</label>
                <label><input type="checkbox" name="q7" value="C">C. 艾莉丝</label>
                <label><input type="checkbox" name="q7" value="D">D. 希露菲</label>
            </div>
            <div id="question8">
                <p id="Question8">8. 请选出属于下图中的动漫的人物（答案可能不止一个）</p>
                <img id="questionImg5" src="./素材/动漫4.jfif" alt="图5">
                <label><input type="checkbox" name="q8" value="A">A. 五条悟</label>
                <label><input type="checkbox" name="q8" value="B">B. 青山七海</label>
                <label><input type="checkbox" name="q8" value="C">C. 七海建人</label>
                <label><input type="checkbox" name="q8" value="D">D. 金木研</label>
            </div>
            <div id="question9">
                <p id="Question9">9. 请写出下图中的动漫中文名称：</p>
                <img id="questionImg6" src="./素材/动漫5.jpg" alt="图6">
                <textarea id="q9" placeholder="请输入您的答案"></textarea>
            </div>
            <div id="question10">
                <p id="Question10">10. 请写出下图中的动漫中文名称：</p>
                <img id="questionImg7" src="./素材/动漫6.png" alt="图7">
                <textarea id="q10" placeholder="请输入您的答案"></textarea>
            </div>
            
            <!-- 添加更多题目 -->
        </div>
        <button id="submitButton" onclick="endExam()" style="display: none;">提交</button>
    </div>

    
    <div id="startDisplay2">
        <h3>考生记录：</h3>
        <table style="text-align: left; border-collapse: collapse; width: 80%; border: 2px solid white;">
            <tr>
                <th style="border: 2px solid white;">姓名</th>
                <th style="border: 2px solid white;">分数</th>
            </tr>
            <!-- 在下面的 ASP 代码中插入考生记录 -->
            <%
            Set conn = Server.CreateObject("ADODB.Connection")
            conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\inetpub\wwwroot\MyWeb\score.mdb"

            Set rs = Server.CreateObject("ADODB.Recordset")
            rs.Open "SELECT s_name, s_score FROM score ORDER BY s_score DESC", conn
            
            Set rs = conn.Execute("SELECT s_name,s_score FROM score ORDER BY s_score DESC")
            While Not rs.EOF
            %>
            <tr>
                <td style="border: 2px solid white;"><%=rs("s_name")%></td>
                <td style="border: 2px solid white;"><%=rs("s_score")%></td>
            </tr>
            <%
                rs.MoveNext
            Wend
            rs.Close
            Set rs = Nothing
            %>
        </table>
    </div>

    <div id="endDisplay" style="display: none;">
        <h1><div id="user"></div></h1>
        <div id="score"></div>
        <div id="usedTime"></div>
    </div>
 


</body>
</html>
