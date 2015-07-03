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
	
	function publishTopics(pageNumber) {
		pageNumber = pageNumber || 0;
		asyncGet('published', {}, 
			buildPublishTopicPage);
	}
	
	function buildPublishTopicPage(topics, pageNumber) {
		document.
		getElementById('published').
		innerHTML = buildTopicsHtml(topics) + createPageChangeButton(pageNumber);
		RegisterPageChangeButtonClick('published', publishTopics);
	}
	
	function joinTopics(pageNumber) {
				asyncGet('joined', {}, 
			buildJoinedTopicPage);
	}
	
	function buildJoinedTopicPage(topics, pageNumber) {
		document.
		getElementById('joined').
		innerHTML = buildTopicsHtml(topics) + createPageChangeButton(pageNumber);
		RegisterPageChangeButtonClick('joined', joinTopics);
	}
	
	function infoCenter(pageNumber) {
		pageNumber = pageNumber || 0;
			
		asyncGet('info-center', {}, 
			buildInfoPage);
	}
	
	function buildInfoPage(topics, pageNumber) {
		document.
		getElementById('info-center').
		innerHTML = buildInfoDetailHtml(topics)	+ createPageChangeButton(pageNumber);
		registerShowDetailLink();
		RegisterPageChangeButtonClick('info-center', infoCenter);		
	}
	
	function createPageChangeButton(pageNumber) {
		return '<div class="change-page-button-group">' +
				'<a class="button" href=' + (parseInt(pageNumber) - 1) +'>上一页</a>' +
				'<a class="button" href=' + (parseInt(pageNumber) + 1) +'>下一页</a>' +
				'</div>';
	}
	
	function RegisterPageChangeButtonClick(divId, func) {
		var changePageButtonsGroup = document.getElementById(divId).
			getElementsByClassName('change-page-button-group').item(0);
		var changePageButtons = 
			changePageButtonsGroup.getElementsByTagName('a');
			
		eachHTMLCollection(changePageButtons, function (button) {
			button.addEventListener('click', function (event) {
				event.preventDefault();
				func(button.getAttribute('href'));
			});
		});
	}
	
	function registerShowDetailLink() {
		var topicLinks = document.
			getElementById('info-center').
			getElementsByTagName('ul').item(0).
			getElementsByTagName('li');
		hiddentopicsDetail();
		
		eachHTMLCollection(topicLinks, function (topicLink) {
			topicLink.getElementsByTagName('a').
			item().addEventListener('click', function () {
				hiddentopicsDetail();
				topicLink.nextElementSibling.style['display'] = 'block';
			});
		});
		
		function hiddentopicsDetail() {
			eachHTMLCollection(topicLinks, function (topicLink) {
				topicLink.nextElementSibling.style['display'] = 'none';
			});
		}
	}
	
	

	function personalInfo() {
		asyncGet('account-manager', {} , buildPersonInfo);
		
	}
	
	function buildPersonInfo(info) {
		document.
		getElementById('account-manager').
		innerHTML = buildInfoHtml(info);

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
				+ (info['status'] ? "已认证":"未认证")	
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
	
	function buildInfoDetailHtml(topics) {
		var ulHtml = '<ul class="links">\n';
		ulHtml += topics.
			map(function (topic) {
				return '<li><a href="#">' + topic.title + '</a></li>\n' + 
						'<div class="topicDetail">' + topic.context + '</div>';
			}).
			reduce(function (topicsHtml, topicHtml) {
				return topicsHtml + topicHtml;
			});
		ulHtml +='</ul>';
		
		return ulHtml;
	}
	
	function buildTopicsHtml(topics) {
		var ulHtml = '<ul class="links">\n';
		ulHtml += topics.
			map(function (topic) {
				return '<li><a href="#">' + topic.title + '</a></li>\n';
			}).
			reduce(function (topicsHtml, topicHtml) {
				return topicsHtml + topicHtml;
			});
		ulHtml +='</ul>';
		
		return ulHtml;
	}
	
	function asyncGet(url, params, func) {
		url += ('?' + urlEncoder(params));
		var xhr = new XMLHttpRequest();
		xhr.open('GET', url, true);
		xhr.setRequestHeader('Accept', 'application/json');		
		xhr.send();
		xhr.onreadystatechange = function () {
//			console.log(JSON.parse(xhr.responseText));
			func(JSON.parse(xhr.responseText));
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
	
	function eachHTMLCollection(tags, func) {
		for (var i = 0; i < tags.length; i++) {
			func(tags.item(i));
		}}
})();