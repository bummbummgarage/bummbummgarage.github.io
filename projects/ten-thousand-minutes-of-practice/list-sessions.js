

$( document ).ready(function() {

	// Add sessins sections
	$("#content").append( "<div id='sessions'></div>" );
	// Add heading to the section
	$("#sessions").append("<h2>Sessions</h2>");
	// Setup table
	$("#sessions").append("<table><thead><tr><th>Date</th><th>Minutes</th><th>Link</th></tr></thead><tbody></tbody></table>");
	// Add entries to the table
	$.get( "https://opensheet.vercel.app/1uzUp3vcmD3A8ZHVXM3ih6do9SHKS0ISE8IcS67cavKY/RawData", function( data ) {

		// Reverse order of elements
		data.reverse();

		// Append html to the table
		$.each(data, function() {

			var row = "<tr>";

			row += "<td>";
			row += $( this )[0].Zeitstempel;
			row += "</td>";

			row += "<td>";
			row += $( this )[0].Minutes;
			row += "</td>";

			// Link
			row += "<td>";
			var link = $( this )[0].Link;
			var text = link.replace("https://","");
			row += "<a style='word-break: break-all;' href='"+link+"'>"+text+"</a>";
			row += "</td>";

			row += "</tr>";

			$("tbody").append( row );

		});

	});

});