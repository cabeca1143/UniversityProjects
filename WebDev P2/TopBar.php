<!-- Top Bar --->
<nav class="navbar navbar-expand-lg navbar-dark">
    <div class="container-fluid">
        <a class="navbar-brand" href="#">My Reviews</a>
        <div class="d-flex align-items-center">
                <span class="navbar-text me-3">
                    Welcome, <?= htmlspecialchars($_SESSION['username']) ?>
                </span>
            <a href="../logout.php" class="btn btn-outline-light">Logout</a>
            <a href="../Profile" class="btn btn-outline-primary me-2" style="margin-left: 5px">Profile</a>
        </div>
    </div>
</nav>