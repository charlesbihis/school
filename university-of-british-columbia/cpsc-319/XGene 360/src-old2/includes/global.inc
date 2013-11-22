<?php

define('LOG_SQL', 'SQLError.log');
define('LOG_LOGIN', 'LoginError.log');

define('UP_INVALID', 0);
define('UP_STUDENT', 1);
define('UP_TA', 2);
define('UP_PROFESSOR', 3);
define('UP_ADMINISTRATOR', 10);

require_once('config.inc');
require_once('classes/Handler/UserHandler.class.php');
require_once('classes/Handler/PageHandler.class.php');

?>