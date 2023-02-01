<?php
// reset cookies
unset($_COOKIE['cookie1']);
unset($_COOKIE['cookie2']);
setcookie('cookie', $_GET["cookie"]);
?>
<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Cookies Test</p>
<?php
echo "Your Cookie: " . $_GET["cookie"];
?>
</div>
</section>
</body>
</html>