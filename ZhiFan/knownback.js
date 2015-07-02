(function () {
	init();
	
	var events = {
		'published': publishTopics,
		'joined': joinTopics,
		'account-manager': personalInfo,
		'info-center': infoCenter
	};
	
	function init() {
		registerTabsClick();
		
		function registerTabsClick() {
			var lis = document.getElementById('tabs').getElementsByTagName('li');
				eachHTMLCollection(lis, _tabchange);
			}
			
			function cleanTabsStatus() {
				var lis = document.getElementById('tabs').getElementsByTagName('li');				
				eachHTMLCollection(lis, function (li) {
					li.removeAttribute('class');
					tabDivNotShow(li);
				});
			}
			
			function _tabchange(li) {
				li.addEventListener('click', function(event) {
					cleanTabsStatus();
					li.setAttribute('class', 'active');
					tabDivShow(li);
					asyncGet('account-manager',{ userid: "13880087240", token: "12348432dfew4dwe" }, function (ds) {console.log(ds);});
				});
			}
			
			function tabDivShow(tab) {
				var tabId = tab.firstChild.getAttribute('for');				
					tabDivShowOrNot(tabId, true);
					events[tabId]();				
			}
			
			function tabDivNotShow(tab) {
				var tabId = tab.firstChild.getAttribute('for');								
					tabDivShowOrNot(tabId, false);			
			}
			
			function tabDivShowOrNot(tabId, isShow) {
				if (isShow) {
					document.getElementById(tabId).style['display'] = 'block';
				} else {
					document.getElementById(tabId).style['display'] = 'none';		
				}

			}
	}
	
	function infoCenter() {
		var topics = ['a', 'b', 'd'];
		document.
		getElementById('info-center').
		innerHTML = buildTopicsHtml(topics);
		
		
		function registerInfoCenterLinkClick() {
			var lis = document.
			getElementById('info-center').
			getElementsByTagName('ul').item(0).
			getElementsByTagName('li');
			eachHTMLCollection(lis, function (li) {
				li.addEventListener	
			});
		}
	}
	
	function publishTopics() {
		var topics = ['a', 'b'];
		document.
		getElementById('published').
		innerHTML = buildTopicsHtml(topics);
	}
	
	function joinTopics() {
		var topics = ['a', 'b', 'c'];
		document.
		getElementById('joined').
		innerHTML = buildTopicsHtml(topics);
	}
	
	function personalInfo() {
		var info = {
			username: 'aa',
			gender: true,
			status: true,
			gold: 23,
			mobile: 2323};
		document.
		getElementById('account-manager').
		innerHTML = buildInfoHtml(info);
	}
	
	function asyncGet(url, params, func) {
		url += ('?' + urlEncoder(params));
		var xhr = new XMLHttpRequest();
		xhr.open('GET', url, true);
		xhr.setRequestHeader('Accept', 'application/json');		
		xhr.send();
		xhr.onreadystatechange = function () {
			func(xhr.responseText);
		};
		
		function urlEncoder(obj) {
			return Object.
			getOwnPropertyNames(obj).
			filter(function (proName) {return typeof(obj[proName]) !== 'function';}).
			filter(function (proName) {return proName !== 'length';}).
			map(function (proName) {return proName + '=' + obj[proName];}).
			join('&');
		}
	}
	
	
	function buildInfoHtml(info) {
		return '<div class="form-group">'
				+ '<label>姓名:</label>'
				+ info['username']
			    + '</div>'
				+ '<div class="form-group">'
				+ '<label>性别:</label>'
				+ (info['gender'] ?'男':'女')
				+ '</div>'
				+ '<div class="form-group">' 
				+ '<label>认证状态:</label>'
				+ info['status']	
				+ '</div>'
				+ '<div class="form-group">'
				+ '<label>积分:</label>'
				+ info['gold']	
				+ '</div>'
				+ '<div class="form-group">'
				+ '<label>手机:</label>'
				+ info['mobile']
				+ '</div>';
	}
	
	function buildTopicsHtml(topics) {
		var ulHtml = '<ul class="links">\n';
		ulHtml += topics.
			map(function (topic) {
				return '<li><a href="#">' + topic + '</a></li>\n';
			}).
			reduce(function (topicsHtml, topicHtml) {
				return topicsHtml + topicHtml;
			});
		ulHtml +='</ul>';
		
		return ulHtml;
	}
	
	function eachHTMLCollection(tags, func) {
		for (var i = 0; i < tags.length; i++) {
			func(tags.item(i));
		}}
})();