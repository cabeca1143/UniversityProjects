<?php

include "../Functions.php";

session_start();

RedirectIfNoId("../Login");

$userId = $_SESSION['userId'];

require "../db.php";

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$stmt = $conn->prepare("SELECT username, email FROM users WHERE id = ?");
$stmt->bind_param("i", $userId);
$stmt->execute();
$user = $stmt->get_result()->fetch_assoc();
$stmt->close();
$conn->close();

$currentUsername = htmlspecialchars($user['username']);
$currentEmail = htmlspecialchars($user['email']);

$message = '';
$message_type = '';
if (isset($_SESSION['message'])) {
    $message = $_SESSION['message'];
    $message_type = $_SESSION['message_type'];
    unset($_SESSION['message'], $_SESSION['message_type']);
}

require "../Head.php";
?>

<title>Profile</title>
<head/>

<body
<div class="container mt-5">
    <div class="row justify-content-center">
        <div class="col-md-8 col-lg-6">
            <div class="card profile-card p-4">
                <div class="text-center mb-4">
                    <h2 class="mt-3" style="color: white;"><?=$currentUsername ?></h2>
                    <p class="mt-2" style="color: white;"><?=$currentEmail ?></p>
                </div>

                <?php if ($message): ?>
                    <div class="alert alert-<?= $message_type === 'success' ? 'success' : 'danger' ?>" role="alert">
                        <?= htmlspecialchars($message) ?>
                    </div>
                <?php endif; ?>

                <form action="updateProfile.php" method="POST">
                    <div class="mb-3">
                        <label for="username" class="form-label" style="color: white;">Change Username</label>
                        <input type="text" class="form-control" id="username" name="username" placeholder="Enter new username">
                    </div>
                    <div class="mb-3">
                        <label for="password" class="form-label" style="color: white;">Change Password</label>
                        <input type="password" class="form-control" id="password" name="password" placeholder="Enter new password">
                    </div>
                    <div class="mb-3">
                        <label for="password_confirmation" class="form-label" style="color: white;">Confirm New Password</label>
                        <input type="password" class="form-control" id="password_confirmation" name="password_confirmation" placeholder="Confirm new password">
                    </div>
                    <div class="d-grid gap-2">
                        <button type="submit" class="btn btn-primary">Save Changes</button>
                        <a href="../Menu" class="btn btn-secondary">Back to Main Menu</a>
                        <a href="deleteAccount.php" class="btn btn-secondary" style="background-color: red; border: red">Delete Account</a>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>
</body>
</html>
