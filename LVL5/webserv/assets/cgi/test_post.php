<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Post Test</p>
<?php
echo "Hello " . $_POST["fpname"] . " You Are " . $_POST["page"] . " Years Old!";
?>
</div>
</section>
</body>
</html>