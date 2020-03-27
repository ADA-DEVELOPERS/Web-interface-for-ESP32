(function($, window, document) {

 
  function IpInput(el, ip, init) {
    var isDigit = ip ? /\d+/.test(ip.replace('.', '')) : '';
    var ipArr = ip ? ip.split('.') : '';
    this.ipArr = ipArr.length == 4 && isDigit ? ipArr : '';
    this.el = el;

    if (init) {
      this._init();
    }
  }

  IpInput.prototype = {
    _init: function() {
      this.el.html(
        '<div class="ip-input-container">' +
          '<input type="text" class="ip-input-item ip1" value="' + (this.ipArr ? this.ipArr[0] : '') + '"/>' + 
          '<i class="ip-input-dot"></i>' + 
          '<input type="text" class="ip-input-item ip2" value="' + (this.ipArr ? this.ipArr[1] : '') + '"/>' +
          '<i class="ip-input-dot"></i>' +
          '<input type="text" class="ip-input-item ip3" value="' + (this.ipArr ? this.ipArr[2] : '') + '"/>' +
          '<i class="ip-input-dot"></i>' +
          '<input type="text" class="ip-input-item ip4" value="' + (this.ipArr ? this.ipArr[3] : '') + '"/>' +
        '</div>'
      );

      this._initEvent();
    },
	
	
	
    _initEvent: function() {

      var preValue;

      this.el.on('focus', 'input', function() {
        preValue = $(this).val();
      }).on('input', 'input', function(e) {
        var $this = $(this);
        var val = $this.val();

        if (val == '.' && preValue != '') {
          $this.val(preValue);
          return;
        }

        var lastChar = val.charAt(val.length - 1);
        val = val.replace(/[^\d]/g, '');

        if (val.length == 3 && lastChar != '.') {
          var next = $this.nextAll('input').eq(0)
          if (next[0]) {
            next.focus();
            selectRange(next[0], 0, next.val().length);
          }
        }
        if (parseInt(val) > 255) {
          val = val.substr(0, val.length - 1);
        }

        $this.val(val);
      }).on('keyup', 'input', function(e) {
        var $this = $(this);        
        var keyCode = e.keyCode;

        if (keyCode == 190) {
          if ($this.val().trim().length > 0) {
            var next = $this.nextAll('input').eq(0)
            if (next[0]) {
              next.focus();
              selectRange(next[0], 0, next.val().length);
            }
          }
        }
        if (keyCode == 8) {
          if ($this.val().trim().length == 0 && preValue == '') {
            var prev = $this.prevAll('input').eq(0)
            if (prev[0]) {
              prev.focus();
              var prevVal = prev.val()
              prev.val(prevVal.slice(0, prevVal.length - 1));
              selectRange(prev[0], prev.val().length, prev.val().length);
            }
          }

          if ($this.val() == '') {
            preValue = '';
          } else {
            preValue = preValue.slice(0, preValue.length - 1);
          }
        }

        if (keyCode != 8 && keyCode != 190) {
          preValue = $this.val();
        }
      })
    },
    
    
    
  }

  $.fn.ipInput = function(ip) {
    return new IpInput(this, ip, true);
  }





})(jQuery, window, document);