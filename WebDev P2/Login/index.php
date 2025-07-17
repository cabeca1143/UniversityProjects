<?php

include "../Functions.php";

session_start();

RedirectIfId("../Menu");

$error_message = '';
if (isset($_SESSION['error_message'])) {
    $error_message = $_SESSION['error_message'];
    unset($_SESSION['error_message']);
}

$success_message = '';
if (isset($_SESSION['success_message'])) {
    $success_message = $_SESSION['success_message'];
    unset($_SESSION['success_message']);
}
require "../Head.php";
?>

<title>Login</title>
<head/>

<body>
<div class="container">
    <div class="form-box">
        <h2>Login</h2>

        <?php if (!empty($error_message)): ?>
            <div class="alert alert-danger" role="alert">
                <?= htmlspecialchars($error_message) ?>
            </div>
        <?php endif; ?>
        <?php if (!empty($success_message)): ?>
            <div class="alert alert-success" role="alert">
                <?= htmlspecialchars($success_message) ?>
            </div>
        <?php endif; ?>

        <form method="POST" action="login.php" class="col">
            <input class="input-field" name="login" placeholder="Username or E-Mail" type="text" required><br>
            <input class="input-field" name="password" placeholder="Password" type="password" required><br>

            <div class="form-check mb-3">
                <input class="form-check-input" type="checkbox" name="remember_me" id="rememberMeCheckbox">
                <label class="form-check-label" for="rememberMeCheckbox">
                    Remember Me
                </label>
            </div>

            <button class="btn btn-primary" type="submit">Login</button>
            <!-- Hack Nothing else worked --->
            <center>
                <p>Don't have an account? <a href="../Registration">Register</a></p>
            </center>
        </form>
    </div>
</div>
</body>
</html>
