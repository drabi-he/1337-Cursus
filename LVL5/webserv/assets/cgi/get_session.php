<?php
    session_start();
?>
<body>
<link rel="stylesheet" href="./style.css">
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <?php
        echo "<h3> PHP List All Session Variables</h3>";
        foreach ($_SESSION as $key=>$val)
        echo "<p>". $key." = ".$val."</p>";
        ?>
</div>
</section>
</body>
</html>