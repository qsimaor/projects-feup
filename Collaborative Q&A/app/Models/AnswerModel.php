<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class AnswerModel extends Model
{
    use HasFactory;
    protected $table = 'answers';
    public $timestamps = false;
    protected $fillable = ['text', 'votes'];
}
