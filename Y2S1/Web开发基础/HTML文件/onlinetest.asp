<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>����ϵͳ</title>
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
                hello = "���Ϻã�" + username + " ����";
            }
            else if (hours >= 12 && hours < 18) {
                hello = "����ã�" + username + " ����";
            }
            else{
                hello = "���Ϻã�" + username + " ����";
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
            
            document.getElementById("timer").innerHTML = "ʣ��ʱ��: " + minutesRemaining + " �� " + secondsRemaining + " ��";

            if (countdown === 0) {
                endExam(); // �Զ��ύ����
            } else {
                countdown--; // ÿ���һ
                setTimeout(displayTime, 1000); // ÿ��һ�������ʾ
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
                alert("�벻Ҫ����հ�����");
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
                alert("���Ķ���ͬ�⿼�Թ���ſɿ�ʼ���ԣ�");
            }
            else if (rule) {
                alert("����д�û����ٿ�ʼ���ԣ�");
            }
            else {
                alert("����д�û������Ķ�ͬ�⿼�Թ���ſɿ�ʼ���ԣ�");
            }
        }

        function endExam() {
            var username = document.getElementById("username").value;
            document.getElementById("examContainer").style.display = "none";
            
            calculateScore();

            // �ύ�����ݵ� process_form.asp����������
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "process_form.asp", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    // ��ת�����Խ���ҳ��
                    window.location.href = "test1.asp";
                }
            };

            // ��������ӵ���������
            xhr.send("username=" + encodeURIComponent(username) + "&score=" + score);
            
            
            document.getElementById("endDisplay").style.display = "block";
            document.getElementById("user").innerHTML = "��ϲ������˿��ԣ�" + username + " ����!";
            document.getElementById("usedTime").innerHTML = "��ʱ: " + minutes + " �� " + seconds + " ��";
            document.getElementById("score").innerHTML = "�÷֣�" + score + " %";

            if (score > 50){
                alert("��ϲ�����õķ�����" + score + "��!");
            }
            else{
                alert("���ź�����ֻ�����"+ score + "�֣��ٽ�����...")
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
                    answer: "ܥ�빬��"
                },
                {
                    answer: "�������Ϸ"
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
        <h1>����ϵͳ</h1>
        <div id="startDisplay">

            <label for="username">�û�����</label>
            <input type="text" id="username" name="username" required><br><br>
            <input type="checkbox" id="readRules" required>
            <label for="readRules">�����Ķ���ͬ��<a href="./ExamRules.html" target="_blank">���Թ���</a></label><br><br>
            <button type="button" id="startButton" onclick="startExam()">��ʼ����</button>

        </div>
        
        <div id="Hello"></div>
        <div id="timer" style="display: none;"></div>
        <div id="questionContainer" style="display: none;">
            <h2>������</h2>
            <div id="question1">
                <p id="Question1">1. ����������һ��������Ʒ���ǳ����ھ����ᣨ������������</p>
                <label><input type="radio" name="q1" value="A">A. �ж���ҲҪ̸����</label>
                <label><input type="radio" name="q1" value="B">B. �����ľ���</label>
                <label><input type="radio" name="q1" value="C">C. ��Ǒ</label>
                <label><input type="radio" name="q1" value="D">D. ������Ů</label>
            </div>
            <div id="question2">
                <p id="Question2">2. ����������һ��������Ʒ���ǳ����ڷɵ��磨Ufotable�� ��</p>
                <label><input type="radio" name="q2" value="A">A. Fate</label>
                <label><input type="radio" name="q2" value="B">B. ������</label>
                <label><input type="radio" name="q2" value="C">C. һȭ����</label>
                <label><input type="radio" name="q2" value="D">D. ����֮��</label>
            </div>
            <div id="question3">
                <p id="Question3">3. ����������һ����Ʒ���ǳ����� MAPPA ��</p>
                <label><input type="radio" name="q3" value="A">A. ���֮Ԩ</label>
                <label><input type="radio" name="q3" value="B">B. ������ս</label>
                <label><input type="radio" name="q3" value="C">C. ������</label>
                <label><input type="radio" name="q3" value="D">D. ��֮��</label>
            </div>
            <div id="question4">
                <p id="Question4">4. ������ͼ�еĻ��������һ��������</p>
                <img id="questionImg1" src="./�ز�/����1.jfif" alt="ͼ1">
                <label><input type="radio" name="q4" value="A">A. Overlord</label>
                <label><input type="radio" name="q4" value="B">B. ��Ҫ��ΪӰ֮ʵ����</label>
                <label><input type="radio" name="q4" value="C">C. һȭ����</label>
                <label><input type="radio" name="q4" value="D">D. ħ��ѧԺ�Ĳ�������</label>
            </div>
            
            <div id="question5">
                <p id="Question5">5. ������ͼ�е������ʲô��</p>
                <img id="questionImg2" src="./�ز�/����1.jpg" alt="ͼ2">
                <label><input type="radio" name="q5" value="A">A. л˹��</label>
                <label><input type="radio" name="q5" value="B">B. �һ��ֽ</label>
                <label><input type="radio" name="q5" value="C">C. ������</label>
                <label><input type="radio" name="q5" value="D">D. ��ľǧ��</label>
            </div>
            <div id="question6">
                <p id="Question6">6. ��ѡ��������ͼ�еĶ���������𰸿��ܲ�ֹһ����</p>
                <img id="questionImg3" src="./�ز�/����2.jfif" alt="ͼ3">
                <label><input type="checkbox" name="q6" value="A">A. �������</label>
                <label><input type="checkbox" name="q6" value="B">B. ʱ�����</label>
                <label><input type="checkbox" name="q6" value="C">C. ��ķ</label>
                <label><input type="checkbox" name="q6" value="D">D. �һ��ֽ</label>
            </div>
            <div id="question7">
                <p id="Question7">7. ��ѡ��������ͼ�еĶ���������𰸿��ܲ�ֹһ����</p>
                <img id="questionImg4" src="./�ز�/����3.jpg" alt="ͼ4">
                <label><input type="checkbox" name="q7" value="A">A. ������</label>
                <label><input type="checkbox" name="q7" value="B">B. ����ϣ</label>
                <label><input type="checkbox" name="q7" value="C">C. ����˿</label>
                <label><input type="checkbox" name="q7" value="D">D. ϣ¶��</label>
            </div>
            <div id="question8">
                <p id="Question8">8. ��ѡ��������ͼ�еĶ���������𰸿��ܲ�ֹһ����</p>
                <img id="questionImg5" src="./�ز�/����4.jfif" alt="ͼ5">
                <label><input type="checkbox" name="q8" value="A">A. ������</label>
                <label><input type="checkbox" name="q8" value="B">B. ��ɽ�ߺ�</label>
                <label><input type="checkbox" name="q8" value="C">C. �ߺ�����</label>
                <label><input type="checkbox" name="q8" value="D">D. ��ľ��</label>
            </div>
            <div id="question9">
                <p id="Question9">9. ��д����ͼ�еĶ����������ƣ�</p>
                <img id="questionImg6" src="./�ز�/����5.jpg" alt="ͼ6">
                <textarea id="q9" placeholder="���������Ĵ�"></textarea>
            </div>
            <div id="question10">
                <p id="Question10">10. ��д����ͼ�еĶ����������ƣ�</p>
                <img id="questionImg7" src="./�ز�/����6.png" alt="ͼ7">
                <textarea id="q10" placeholder="���������Ĵ�"></textarea>
            </div>
            
            <!-- ��Ӹ�����Ŀ -->
        </div>
        <button id="submitButton" onclick="endExam()" style="display: none;">�ύ</button>
    </div>

    
    <div id="startDisplay2">
        <h3>������¼��</h3>
        <table style="text-align: left; border-collapse: collapse; width: 80%; border: 2px solid white;">
            <tr>
                <th style="border: 2px solid white;">����</th>
                <th style="border: 2px solid white;">����</th>
            </tr>
            <!-- ������� ASP �����в��뿼����¼ -->
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
