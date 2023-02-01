<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Get Test</p>
<?php
echo "Hello " . $_GET["lgname"] . " " . $_GET["fgname"] . " !";
?>
</div>
</section>
</body>
</html>