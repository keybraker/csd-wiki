
function a() { return 10; }
function b() { return (function() { return 11; }); }
function c() { return 12; }

(function(a,b,c){::print(a);})(a(), b()(), (function(x){return x;})(c()));



