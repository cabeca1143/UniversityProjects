<?php

include "../Functions.php";

session_start();

CheckCookie();

if (!isset($_SESSION['userId'])) {
    header('Location: ../Login');
    exit();
}

//Load database stuff here?

$message = '';
$message_type = '';
if (isset($_SESSION['message'])) {
    $message = $_SESSION['message'];
    $message_type = $_SESSION['message_type'];
    unset($_SESSION['message'], $_SESSION['message_type']);
}

require "../Head.php";
?>
<title>Edit</title>
</head>

<body>
    <div class="container mt-5">
        <div class="row justify-content-center">
            <div class="col-md-8 col-lg-6">
                <div class="card edit-card p-4">
                    <h2 class="text-center mb-4" style="color: white">Edit Review</h2>

                    <?php if ($message): ?>
                        <div class="alert alert-<?= $message_type === 'success' ? 'success' : 'danger' ?>" role="alert">
                            <?= htmlspecialchars($message) ?>
                        </div>
                    <?php endif; ?>

                    <!-- TODO: Finish the script and network stuff here -->
                    <form action="TODO.php" method="POST">
                        <input type="hidden" name="reviewId" value="Lorem">

                        <div class="mb-3">
                            <label for="title" class="form-label">Title</label>
                            <input type="text" class="form-control" id="title" name="title" value="Test" required>
                        </div>
                        <div class="mb-3">
                            <label for="image" class="form-label">Image URL (Optional)</label>
                            <input type="url" class="form-control" id="image" name="image" value="">
                        </div>
                        <div class="mb-3">
                            <label for="rating" class="form-label">Rating</label>
                            <input type="number" class="form-control" id="rating" name="rating" min="1" max="5" value="" required>
                        </div>
                        <div class="mb-3">
                            <label for="description" class="form-label">Comment</label>
                            <textarea class="form-control" id="description" name="description" rows="4"></textarea>
                        </div>

                        <div class="d-grid gap-2 d-md-flex justify-content-md-between">
                            <!-- Update Button -->
                            <button type="submit" name="action" value="update" class="btn btn-primary">Save Changes</button>
                            <!-- Delete Button -->
                            <button type="submit" name="action" value="delete" class="btn btn-danger" onclick="return confirm('Are you sure you want to delete this review?');">Delete Review</button>
                        </div>

                        <div class="d-grid mt-3">
                            <a href="../Menu" class="btn btn-secondary">Back to Main Menu</a>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
