formatter = "%r %r %r %r"

print formatter % (1, 2, 3, 4)
print formatter % ("one", "two", "three", "four")
print formatter % (True, False, False, True)
print formatter % (formatter, formatter, formatter, formatter)
print formatter % (
	"I had this thing.",
	"That you could type up right.",
	"But it did't sing.",
	"So I said goodnight."
)

# Q: Why the last line's print has both ' and "?
print "------"
print formatter % ("one", 2, True, 4)
print formatter % (
	"One.",
	"Two.",
	"Three.",
	"Four."
)
print formatter % (
	"I had this thing.",
	"That you could type up right.",
	"But it did not sing.",
	"Four"
)
print formatter % (
	"I had this thing.",
	"That you could type up right.",
	'But "it" did not sing.',
	"Four"
)
print formatter % (
	"I had this thing.",
	"That you could type up right.",
	'But "it" did not sing.',
	'''You said "OK", it means 'OK'.'''
)
print formatter % (
	"I had this thing.",
	"That you could type up right.",
	'But "it" did not sing.',
	"""You said "OK", it means 'OK'.
	And more.
	More and more."""
)
# I found it's because it has ' in "xxxx"