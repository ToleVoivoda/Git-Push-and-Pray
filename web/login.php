<?php
    session_start();
    //include "db_connection.php";
?>

<!DOCTYPE html>
<html lang="bg">

<head>
    <meta charset="UTF-8">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/css/index.css">
    <link rel="stylesheet" href="css/login.css">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <title>Safe streets</title>
</head>

<body>
    <main class="login-main">
        <div class="img-box">
            <img src="img/loginimg.png" />
        </div>
        <div class="login-box">
            <h2 class="loginheading">Вход</h2>
            <form id="login-form" class="login-form" action="login-action.php" method="post">
                <div class="form-floating mb-3 mt-3">
                    <input type="email" class="form-control" id="email" placeholder="Въведете имейл" name="email">
                    <label for="email">Имейл</label>
                </div>

                <div class="form-floating mt-3 mb-3">
                    <input type="password" class="form-control" id="password" placeholder="Въведете парола" name="password">
                    <label for="pass">Парола</label>
                </div>

                <div class="login-additional">
                    <span ><a href="register.php">Нямате профил? Регистрация</a></span>
                </div>
                
                <input class="login-button" type="submit" value="Вход">
            </form>
        </div>
    </main>
</body>
</html>