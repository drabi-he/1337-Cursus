<?php
session_start();
unset($_SESSION);
session_destroy();
?>
<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Session Test</p>
<?php
echo 'Session Has Been Destroyed';
?>
</div>
</section>
</body>
</html>