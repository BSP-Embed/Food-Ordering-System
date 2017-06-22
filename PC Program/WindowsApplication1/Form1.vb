﻿Imports System.IO.Ports
Imports System.Data
Imports System.Data.OleDb
Imports System.IO

Public Class Form3

    Private WithEvents comPort As New IO.Ports.SerialPort
    Private dataIn As String
    Private Fooditem As String
    Private readBuffer As String = String.Empty
    Private Bytenumber As Integer
    Private ByteToRead As Integer
    Private TotalAmount As Integer

    Private byteEnd(2) As Char
    Private comOpen As Boolean

    Dim swriter As StreamWriter

    Private Sub Form3_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        Disconnect()
    End Sub
    Private Sub Form3_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Timer1.Enabled = True
        AddHandler comPort.DataReceived, AddressOf comPort_DataReceived
    End Sub
    Public Sub Disconnect()

        If comPort IsNot Nothing AndAlso comPort.IsOpen Then
            comPort.Close()
        End If
    End Sub
    Private Sub comPort_DataReceived(ByVal sender As Object, ByVal e As SerialDataReceivedEventArgs)
        If comOpen Then
            Try

                Dim bytes As Integer = comPort.BytesToRead
                'create a byte array to hold the awaiting data
                Dim comBuffer As Byte() = New Byte(bytes - 1) {}
                'read the data and store it

                comPort.Read(comBuffer, 0, bytes)

                If comBuffer(0) = 1 Then
                    TotalAmount = TotalAmount + 99
                    If comBuffer(1) = 1 Then
                        Fooditem = "Burger" + " ( spicy )"
                    Else
                        Fooditem = "Burger" + " ( Normal ) "
                    End If
                    ListBox1.Items.Add(Fooditem)
                    MsgBox("items Ordered From Table 1")
                End If

                If comBuffer(0) = 2 Then
                    TotalAmount = TotalAmount + 49
                    If comBuffer(1) = 1 Then
                        Fooditem = "Fries" + " ( spicy )"
                    Else
                        Fooditem = "Fires" + " ( Normal ) "
                    End If
                    ListBox1.Items.Add(Fooditem)
                    MsgBox("items Ordered From Table 1")
                End If

                If comBuffer(0) = 3 Then
                    TotalAmount = TotalAmount + 29
                    ListBox1.Items.Add("ICE SCREAM")
                    MsgBox("items Ordered From Table 1")
                End If

                If comBuffer(0) = 4 Then
                    TotalAmount = TotalAmount + 59

                    ListBox1.Items.Add("COKE")
                    MsgBox("items Ordered From Table 1")
                End If

                If comBuffer(0) = 5 Then
                    MsgBox("Ordered Over From Table 1")
                    display()
                End If

                TextBox8.Text = TotalAmount

                comPort.Write("s")
            Catch ex As Exception
                MsgBox("Read " & ex.Message)
            End Try
        End If
    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Close()
        Me.Dispose()
    End Sub
    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Label6.Text = TimeOfDay
    End Sub
    Private Sub display()

        System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = False
        swriter = File.AppendText("database.txt")

        swriter.WriteLine("**********************************")
        swriter.WriteLine("Food Ordering System")
        swriter.WriteLine("Date         Time     Items     Total")
        swriter.WriteLine("*************************************")

        swriter.WriteLine(Date.Now())

        For l_index As Integer = 0 To ListBox1.Items.Count - 1
            Dim l_text As String = CStr(ListBox1.Items(l_index))
            swriter.WriteLine(l_text)
        Next
        swriter.WriteLine(TextBox8.Text)
        swriter.Close()
        Button2.Enabled = True
    End Sub
    Private Sub Button2_Click_1(sender As Object, e As EventArgs) Handles Button2.Click
        ListBox1.Items.Clear()
        TextBox8.Text = ""
    End Sub
    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        With comPort
            .PortName = TextBox3.Text
            .BaudRate = 9600
            .Parity = IO.Ports.Parity.None
            .DataBits = 8
            .StopBits = IO.Ports.StopBits.One
            .Handshake = IO.Ports.Handshake.None
            .RtsEnable = False
            .ReceivedBytesThreshold = 2            'threshold: one byte in buffer > event is fired 

        End With

        Try
            comPort.Open()
            comOpen = comPort.IsOpen
        Catch ex As Exception
            comOpen = False
            Label20.Text = "NOT CONNECTED"
            MsgBox("Error Open: " & ex.Message)
        End Try
        If comOpen = True Then
            Label20.Text = "CONNECTED"

        End If
    End Sub
End Class