function Lecture(name, teacher)
{
	this.name = name;
	this.teacher = teacher;
}
Lecture.prototype.display = function(){
	return this.teacher + " is teaching " + this.name;
}

function Schedule(lectures){
	this.lectures = lectures;
}

Schedule.prototype.display = function(){
	var str = "";
	for (var i = 0; i < this.lectures.length; i++)
		str += this.lectures[i].display + " ";

	return str;
}

var mySchedule = new Schedule([
		new Lecture("Gym", "Mr. Smith"),
		new Lecture("Math", "Mrs. Jones"),
		new Lecture("English", "TBD")
	]);
alert(mySchedule.display());
