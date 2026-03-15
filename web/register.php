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
    <main>
        <div class="img-box-reg">
            <img class="register-img" src="img/registerimg2.png"/>
        </div>
        <div class="register-box">
            <h2 class="loginheading">Регистрация</h2>
            <form id="register-form" action="register-action-try2.php" method="post">
                <div class="form-floating mb-3 mt-3">
                    <input type="text" class="form-control" id="firstname" placeholder="Въведете име" name="firstname">
                    <label for="firstname">Име</label>
                </div>
                
                <div class="d-flex register-checkboxes">
                    <div class="form-check">
                        <input type="radio" id="woman" name="gender" value=1 class="form-check-input" checked/>Жена
                        <label class="form-check-label" for="woman"></label>
                    </div>
                    <div class="formь-check">
                        <input type="radio" id="man" value=1 name="gender" class="form-check-input" />Мъж
                        <label class="form-check-label" for="man"></label>
                    </div>
                </div>

                <div class="form-floating mt-3 mb-3">
                    <input type="text" class="form-control" id="phone" placeholder="Въведете телефон" name="phone" autocomplete="off">
                    <label for="phone">Телефон</label>
                </div>

                <div class="form-floating mb-3 mt-3">
                    <input type="email" class="form-control" id="email" placeholder="Въведете имейл" name="email" autocomplete="off">
                    <label for="email">Имейл</label>
                </div>


                <div class="form-floating mt-3 mb-3">
                    <input type="password" class="form-control" id="password" placeholder="Въведете парола" name="password">
                    <label for="password">Парола</label>
                </div>
                <div class="form-floating mt-3 mb-3">
                    <input type="text" class="form-control" id="password2" placeholder="Повторете паролата" name="password2">
                    <label for="password2">Повторете паролата</label>
                </div>
                <div class="login-additional">
                    <span ><a href="login.php">Имате профил? Вход</a></span>
                </div>

                <input class="login-button" type="submit" value="Регистрирай се">
            </form>
        </div>
    </main>
</body>
</html>








