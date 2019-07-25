.name "A-team"
.comment "A real champion"

destroy:	sti r1, %:go, %1
			and r1, %0, r1
			sti r1, %:destroy, %0
go:			live %1
			zjmp %:go
