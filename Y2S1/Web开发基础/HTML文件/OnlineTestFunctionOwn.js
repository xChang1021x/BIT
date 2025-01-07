var userAnswers = {};
var incorrectAnswers = {};
var isSubmitted = false;
var timeStart;
var time;
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
}

function updateTimer() {
    var currentTime = new Date();
    var timeDiff = currentTime - timeStart;
    seconds = Math.floor(timeDiff / 1000);
    minutes = Math.floor(seconds / 60);
    seconds = seconds % 60;
    document.getElementById("timer").innerHTML = "用时: " + minutes + " 分 " + seconds + " 秒";
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
        alert("请填写用户名并阅读同意考试规则才可开始考试！")
    }
}

function endExam() {
    var username = document.getElementById("username").value;
    document.getElementById("examContainer").style.display = "none";

    calculateScore();

    document.getElementById("endDisplay").style.display = "block";
    document.getElementById("user").innerHTML = "恭喜您完成了考试，" + username + " 考生!";
    document.getElementById("usedTime").innerHTML = "用时: " + minutes + " 分 " + seconds + " 秒";
    document.getElementById("score").innerHTML = "得分：" + score * 10 + " %";
    document.getElementById("incorrectAnswers").innerHTML = incorrectAnswers;

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

}