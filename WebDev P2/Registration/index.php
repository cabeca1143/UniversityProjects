<?php
include "../Functions.php";

session_start();

RedirectIfId("../Menu");

$error_message = '';
if (isset($_SESSION['error_message'])) {
    $error_message = $_SESSION['error_message'];
    unset($_SESSION['error_message']);
}

require "../Head.php";
?>

<title>Register</title>
<head/>

<body>
<div class="container">
    <div class="form-box">
        <h2>Register</h2>

        <?php if (!empty($error_message)): ?>
            <div class="alert alert-danger" role="alert">
                <?= htmlspecialchars($error_message) ?>
            </div>
        <?php endif; ?>

        <!-- The form's action should point to the backend processing script -->
        <form method="POST" action="register.php" class="col">

            <input class="input-field" name="username" placeholder="Username" type="text" required><br>
            <input class="input-field" name="email" placeholder="E-Mail" type="email" required><br>
            <input class="input-field" name="password" placeholder="Password" type="password" required><br>
            <input class="input-field" name="password_confirmation" placeholder="Confirm your Password" type="password" required><br>

            <button class="btn btn-primary" type="submit">Register</button>
            <center>
                <p>Already have an account? <a href="../Login">Login</a></p>
            </center>
        </form>
    </div>
</div>
</body>
</html>
