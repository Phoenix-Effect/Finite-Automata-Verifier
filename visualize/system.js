var nodes = [
	{id: 1, label: '1', color: '#FF7F32'},
	{id: 2, label: '2', color: '#5C6670'},
	{id: 3, label: '3', color: {background:'#78BE20', border:'green'}},
	{id: 5326, label: 'Dead-State', color: '#5C6670'},
	{id: 14, label: '14', color: {background:'#78BE20', border:'green'}},
	{id: 24, label: '24', color: {background:'#78BE20', border:'green'}}
];

var edges = [
	{from: 1, to:2, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 1, to:3, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 2, to:2, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 2, to:5326, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 3, to:14, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 3, to:5326, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 5326, to:5326, arrows:'to', label: 'a, b', font: {align: 'top'}},
	{from: 14, to:24, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 14, to:3, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 24, to:24, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 24, to:3, arrows:'to', label: 'b', font: {align: 'top'}}
];