var nodes = [
	{id: 1, label: '1', color: {background:'#FF7F32', border:'green'}},
	{id: 2, label: '2', color: '#5C6670'},
	{id: 3, label: '3', color: {background:'#78BE20', border:'green'}}
];

var edges = [
	{from: 1, to:2, arrows:'to', label: 'a, g', font: {align: 'top'}},
	{from: 1, to:1, arrows:'to', label: 'b, c, d, e, f', font: {align: 'top'}},
	{from: 2, to:2, arrows:'to', label: 'a, c, d, e, f, g', font: {align: 'top'}},
	{from: 2, to:3, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 3, to:3, arrows:'to', label: 'a, b, c, d, e, f, g', font: {align: 'top'}}
];