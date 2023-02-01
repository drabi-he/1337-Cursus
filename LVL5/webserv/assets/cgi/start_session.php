<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
    $_SESSION["NewSession"] = "NewSession";
}
?>
<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Session Test</p>
<?php
echo 'Session Has Started';
?>
</div>
</section>
</body>
</html>