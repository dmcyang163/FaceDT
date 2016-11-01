from datetime import date, time, datetime, timedelta
import time
import os

def hello():
	#print "hello world."
	os.popen("/home/pi/tom/test/faceDT/run.sh")
	#while 1:
	#	os.popen("/home/pi/tom/test/faceDT/run.sh")
	#	time.sleep(5)


def runTask(func, day=0, hour=0, min=0, second=10):
	# get current time 
	now = datetime.now()
	strnow = now.strftime('%Y-%m-%d %H:%M:%S')
	print "now:",strnow
	# get net_run time
	period = timedelta(days=day, hours=hour, minutes=min, seconds=second)
	next_time = now + period
	strnext_time = next_time.strftime('%Y-%m-%d %H:%M:%S')
	print "next run:",strnext_time
	while True:
		now = datetime.now()
		strnow = now.strftime('%Y-%m-%d %H:%M:%S')
		# if system time eq next_time run the specific task(hello func)
		if str(strnow) == str(strnext_time):
			print strnow
			func()
			print "task done."
			break

if __name__ == '__main__':
	runTask(hello, second=10)
	while 1:
		print "\n33333333333333333333333333333333\n"
		time.sleep(1)
