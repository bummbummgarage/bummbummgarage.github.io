

$( document ).ready(function() {

	// Add sessins sections
	$("#content").append( "<div id='sessions'></div>" );
	// Add heading to the section
	$("#content").append("<h2>Sessions</h2>");
	// Setup table
	$("#content").append("<table><thead><tr><th>Date</th><th>Minutes</th><th>Link</th></tr></thead><tbody></tbody></table>");
	// Add entries to the table
	$.get( "https://opensheet.vercel.app/1uzUp3vcmD3A8ZHVXM3ih6do9SHKS0ISE8IcS67cavKY/RawData", function( data ) {

		$.each(data, function() {

			var row = "<tr>";

			row += "<td>";
			row += $( this )[0].Zeitstempel;
			// console.log( $( this )[0].Zeitstempel );
			row += "</td>";

			row += "<td>";
			row += $( this )[0].Minutes;
			// console.log( $( this )[0].Minuten );
			row += "</td>";

			row += "<td>";
			row += $( this )[0].Link;
			// console.log( $( this )[0].Link );
			row += "</td>";

			row += "</tr>";

			$("tbody").append( row );

		});

	});

});