<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Cookies Test</p>
<?php
$cookie = htmlspecialchars($_COOKIE['cookie']);
echo "Cookie: " . $cookie
?>
</div>
</section>
</body>
</html>