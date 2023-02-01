<?php
session_start();
$_SESSION[$_POST["key"]]=$_POST["value"];
?>

<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Session Test</p>
<?php
echo $_POST["key"] . "=" . $_POST["value"] . " is now set!";
?>
</div>
</section>
</body>
</html>

