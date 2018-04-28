var nodes = [
	{id: 595, label: '1SP#', color: '#FF7F32'},
	{id: 596, label: '2SP#', color: {background:'#78BE20', border:'green'}},
	{id: 597, label: '3SP#', color: '#5C6670'}
];

var edges = [
	{from: 595, to:596, arrows:'to', label: 'a, g', font: {align: 'top'}},
	{from: 595, to:595, arrows:'to', label: 'b, c, d, e, f', font: {align: 'top'}},
	{from: 596, to:596, arrows:'to', label: 'a, c, d, e, f, g', font: {align: 'top'}},
	{from: 596, to:597, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 597, to:597, arrows:'to', label: 'a, b, c, d, e, f, g', font: {align: 'top'}}
];