// 声明全局的用户答案对象和计时器
var userAnswers = {};
var isSubmitted = false;
var startTime;
var timerInterval;

function startExam() {
    var username = document.getElementById("username").value;
    var readRules = document.getElementById("readRules").checked;
    var blankCnt = 0;
    for (var i = 0; i < username.length; i++) {
        if (username[i] == ' ') {
            blankCnt++;
        }
    }
    if (username && blankCnt == username.length) {
        alert("请不要输入空白名字！");
    }
    else if (username && readRules) {
        document.getElementById("timer").style.display = "block";
        document.getElementById("questionContainer").style.display = "block";
        document.getElementById("startButton").style.display = "none";
        document.getElementById("submitButton").style.display = "block";

        displayGreeting();
        loadQuestions(); // 调用加载题目函数
        startTimer(); // 开始计时
    } else {
        alert("请填写用户名并同意考试规则才能开始考试！");
    }
}

function displayGreeting() {
    var username = document.getElementById("username").value;
    var now = new Date();
    var hours = now.getHours();
    var greeting = "";
    if (hours >= 6 && hours < 12) {
        greeting = "早上好 " + username;
    } else if (hours >= 12 && hours < 18) {
        greeting = "下午好 " + username;
    } else {
        greeting = "晚上好 " + username;
    }
    document.getElementById("greeting").innerHTML = greeting;
}

// 在提交按钮的click事件中调用calculateScore函数
document.getElementById("submitButton").addEventListener("click", function () {

    if (!isSubmitted) {
        isSubmitted = true;
        stopTimer(); // 停止计时
        calculateScore();
    } else {
        var confirmSubmit = confirm("您已经提交过了，确定要再次提交吗？");
        if (confirmSubmit) {
            calculateScore();
        }
    }
});

// 在加载题目时调用的函数
function loadQuestions() {
    var questions = [
        {
            question: "请问下列哪一部动画作品不是出自于京阿尼（京都动画）？",
            correctAnswer: "B"
        },
        {
            question: "请问下列哪一部动画作品不是出自于飞碟社（Ufotable） ？",
            correctAnswer: "C"
        },
        {
            question: "请问下列哪一部作品不是出自于 MAPPA ？",
            correctAnswer: "D"
        },
        {
            question: "请问下图中的画面出自哪一部动漫？",
            correctAnswer: "B"
        },
        {
            question: "请问下图中的人物叫什么",
            correctAnswer: "A"
        },
        {
            question: "请选出属于下图中的动漫的人物（答案可能不止一个）",
            correctAnswer: ["A", "B", "D"]
        },
        {
            question: "请选出属于下图中的动漫的人物（答案可能不止一个）",
            correctAnswer: ["B", "C", "D"]
        },
        {
            question: "请选出属于下图中的动漫的人物（答案可能不止一个）",
            correctAnswer: ["A", "B", "C"]
        },
        
        // 添加更多题目
    ];

    for (let i = 0; i < questions.length; i++) {
        var questionDiv = document.getElementById("question" + (i + 1));
        questionDiv.querySelector("p").textContent = (i + 1) + ". " + questions[i].question;
        if (Array.isArray(questions[i].correctAnswer)) {
            var checkboxes = questionDiv.querySelectorAll("input[type=checkbox]");
            for (var j = 0; j < checkboxes.length; j++) {
                checkboxes[j].addEventListener("change", function () {
                    updateUserCheckboxAnswers(i);
                });
            }
        } else {
            var radios = questionDiv.querySelectorAll("input[type=radio]");
            for (var k = 0; k < radios.length; k++) {
                radios[k].addEventListener("change", function () {
                    updateUserRadioAnswer(i);
                });
            }
        }
    }
}

// 更新用户的单选题答案
function updateUserRadioAnswer(questionIndex) {
    var radios = document.getElementsByName("q" + (questionIndex + 1));
    for (var i = 0; i < radios.length; i++) {
        if (radios[i].checked) {
            userAnswers["q" + (questionIndex + 1)] = radios[i].value;
            break;
        }
    }
}

// 更新用户的多选题答案
function updateUserCheckboxAnswers(questionIndex) {
    var checkboxes = document.getElementsByName("q" + (questionIndex + 1));
    var selectedAnswers = [];
    for (var i = 0; i < checkboxes.length; i++) {
        if (checkboxes[i].checked) {
            selectedAnswers.push(checkboxes[i].value);
        }
    }
    userAnswers["q" + (questionIndex + 1)] = selectedAnswers;
}

// 计算得分
function calculateScore() {
    var correctAnswers = {
        q1: "B",
        q2: "C",
        q3: "D",
        q4: "B",
        q5: "A",
        q6: ["A", "B", "D"],
        q7: ["B", "C", "D"],
        q8: ["A", "B", "C"]
    };

    var score = 0;
    var incorrectAnswers = [];

    for (var questionId in userAnswers) {
        if (userAnswers.hasOwnProperty(questionId)) {
            var userAnswer = userAnswers[questionId];
            var correctAnswer = correctAnswers[questionId];

            if (Array.isArray(userAnswer)) {
                if (arraysEqual(userAnswer, correctAnswer)) {
                    score++;
                } else {
                    incorrectAnswers.push(questionId);
                }
            } else {
                if (userAnswer === correctAnswer) {
                    score++;
                } else {
                    incorrectAnswers.push(questionId);
                }
            }
        }
    }

    displayScore(score, incorrectAnswers);
}


// 显示得分和相关信息
function displayScore(score, incorrectAnswers) {
    var endTime = new Date();
    var timeDiff = endTime - startTime;
    var seconds = Math.floor(timeDiff / 1000);
    var minutes = Math.floor(seconds / 60);
    seconds = seconds % 60;
    document.getElementById("score").innerHTML = "得分: " + score;
    document.getElementById("timer").innerHTML = "用时: " + minutes + " 分 " + seconds + " 秒";
    if (incorrectAnswers.length > 0) {
        document.getElementById("incorrectAnswers").innerHTML = "答错的题目: " + incorrectAnswers.join(", ");
    }
    document.getElementById("score").style.display = "block";
    document.getElementById("incorrectAnswers").style.display = "block";
    document.getElementById("timer").style.display = "block";
    document.getElementById("submitButton").style.display = "none";
}

// 比较两个数组是否相等
function arraysEqual(arr1, arr2) {
    if (arr1.length !== arr2.length) return false;
    for (var i = 0; i < arr1.length; i++) {
        if (arr1[i] !== arr2[i]) return false;
    }
    return true;
}

// 启动计时器
function startTimer() {
    startTime = new Date();
    timerInterval = setInterval(updateTimer, 1000);
}

// 更新计时器
function updateTimer() {
    var currentTime = new Date();
    var timeDiff = currentTime - startTime;
    var seconds = Math.floor(timeDiff / 1000);
    var minutes = Math.floor(seconds / 60);
    seconds = seconds % 60;
    document.getElementById("timer").innerHTML = "用时: " + minutes + " 分 " + seconds + " 秒";
}

// 停止计时器
function stopTimer() {
    clearInterval(timerInterval);
}
