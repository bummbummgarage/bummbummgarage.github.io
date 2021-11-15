

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
			var d = parseGermanDate( $( this )[0].Zeitstempel );
			year = d.getFullYear();
			monthIndex = d.getMonth();
			monthName = months[monthIndex];
			day = d.getDate();
			row += day + " " + monthName + " " + year;

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


// Parse german date format.
// As seen on https://stackoverflow.com/a/2945150
function parseGermanDate(input) {
  var parts = input.match(/(\d+)/g);
  // note parts[1]-1
  return new Date(parts[2], parts[1]-1, parts[0]);
}

// Getting the month names
// As seen on https://css-tricks.com/everything-you-need-to-know-about-date-in-javascript/
const months = [
  'January',
  'February',
  'March',
  'April',
  'May',
  'June',
  'July',
  'August',
  'September',
  'October',
  'November',
  'December'
]

